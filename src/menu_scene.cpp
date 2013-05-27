/**
 * Copyright (C) 2013
 * Christian Fischer
 *
 * https://bitbucket.org/baldur/wiesel/
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 */
#include "menu_scene.h"
#include "wiesel/video/video_driver.h"

#include <wiesel/graph/2d/rect_shape_node.h>
#include <wiesel/ui/label_node.h>

using namespace wiesel;


#define BUTTON_R			(0.0f)
#define BUTTON_G			(0.0f)
#define BUTTON_B			(0.8f)

#define BUTTON_SELECTED_R	(0.5f)
#define BUTTON_SELECTED_G	(0.5f)
#define BUTTON_SELECTED_B	(1.0f)



MenuScene::MenuScene(ApiDemosApp *app, SceneBase *previous) : SceneBase(app, previous) {
	selected_item = NULL;
	total_height  = 0.0f;
	scroll_offset = 0.0f;

	scroll_offset_node = new Node2D();

	scroll_node = new Node2D();
	scroll_node->addChild(scroll_offset_node);

	this->addChild(scroll_node);

	// configure viewport
	this->setScaleMode(
			Viewport::FitToParent,
			dimension(200, 200)
	);

	return;
}

MenuScene::~MenuScene() {
}


void MenuScene::addMenuEntry(const std::string& title, SceneFactory factory) {
	dimension button_size(200, 18);
	float button_gap   = 2.0f;

	LabelNode *label = new LabelNode();
	label->setFont(getApplication()->getDefaultFont());
	label->setText(title);
	label->setPivot(0.5f, 0.5f);
	label->setPosition(button_size.width/2, button_size.height/2);

	RectShapeNode *rect = new RectShapeNode(button_size);
	rect->setColor(0.0f, 0.0f, 0.8f);
	rect->setPivot(0.5f, 1.0f);
	rect->setPosition(0.0f, -(total_height));
	rect->addChild(label, 1);

	scroll_offset_node->addChild(rect);

	MenuItem menu_item;
	menu_item.title		= title;
	menu_item.node		= rect;
	menu_item.factory	= factory;
	menu_item_list.push_back(menu_item);

	total_height += button_gap;
	total_height += button_size.height;

	return;
}


void MenuScene::onViewportChanged(const rectangle& old_viewport, const rectangle& new_viewport) {
	SceneBase::onViewportChanged(old_viewport, new_viewport);

	scroll_node->setPosition(new_viewport.size.width/2, new_viewport.size.height);

	return;
}


void MenuScene::onTouchStarted(wiesel::Touch *touch) {
	if (touch->getTouchID() == 0) {
		touch->claim(this);

		assert(selected_item == NULL);
		for(std::list<MenuItem>::iterator it=menu_item_list.begin(); it!=menu_item_list.end(); it++) {
			vector2d nodespace = it->node->convertWorldToLocal(touch->getScreenLocation());

			if (it->node->hitBy(nodespace)) {
				selected_item = &(*it);
				selected_item->node->setColor(BUTTON_SELECTED_R, BUTTON_SELECTED_G, BUTTON_SELECTED_B);
			}
		}
	}

	return;
}


void MenuScene::onTouchMoved(const wiesel::Touch *touch) {
	if (touch->getTouchID() == 0) {
		vector2d moved = (touch->getOriginalLocation() - touch->getScreenLocation());
		float sq_distance = (moved.x*moved.x) + (moved.y*moved.y);

		// de-select on move
		if (selected_item && (sq_distance > 100)) {
			Log::info << "wiesel distance moved: " << sq_distance << std::endl;
			selected_item->node->setColor(BUTTON_R, BUTTON_G, BUTTON_B);
			selected_item = NULL;
		}

		// move, when no item selected
		if (selected_item == NULL) {
			float new_scroll_offset =
					(touch->getScreenLocation().y - touch->getOriginalLocation().y)
				/	this->getWorldTransform().m22
			;

			scroll_offset_node->setPosition(0, clipScrollOffset(scroll_offset + new_scroll_offset));
		}
	}

	return;
}


void MenuScene::onTouchEnded(const wiesel::Touch *touch) {
	if (touch->getTouchID() == 0) {
		float new_scroll_offset =
				(touch->getScreenLocation().y - touch->getOriginalLocation().y)
			/	this->getWorldTransform().m22
		;

		scroll_offset = clipScrollOffset(scroll_offset + new_scroll_offset);

		if (selected_item) {
			if (selected_item->factory) {
				Scene* new_scene = selected_item->factory(getApplication(), this);
				if (new_scene) {
					getApplication()->clearSceneStack();
					getApplication()->pushScene(new_scene);
				}
			}

			selected_item->node->setColor(BUTTON_R, BUTTON_G, BUTTON_B);
			selected_item = NULL;
		}
	}

	return;
}


float MenuScene::clipScrollOffset(float offset) {
	const float scroll_max = (total_height - this->getViewport().size.height);
	if (offset > scroll_max) {
		offset = scroll_max;
	}

	if (offset < 0) {
		offset = 0;
	}

	return offset;
}
