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
#include "scene_base.h"
#include "button.h"
#include "wiesel/resources/graphics/spritesheet.h"

#include <sstream>

using namespace wiesel;


SceneBase::SceneBase(ApiDemosApp *app, SceneBase *previous) {
	assert(app);

	this->app			= app;
	this->previous		= previous;

	this->frame_count	= 0.0f;
	this->frame_time	= 0.0f;
	this->timeout		= 0.0f;

	// create FPS label
	fps_label = new LabelNode();
	fps_label->setFont(app->getDefaultFont());
	fps_label->setPivot(0.0f, 0.0f);
	fps_label->setPosition(0.0f, 0.0f);
	this->addChild(fps_label, 1000);

	// create back-button
	if (previous) {
		bt_back = new Button(
				getApplication()->getHudSpritesheet()->get("button_left"),
				getApplication()->getHudSpritesheet()->get("button_left_selected"),
				this,
				(Button::OnButtonClicked)&SceneBase::onButtonBack
		);

		bt_back->setPivot(0.0f, 1.0f);
		this->addChild(bt_back, 1000);
	}

	// register for frame updates
	Engine::getInstance()->registerUpdateable(this);

	return;
}


SceneBase::~SceneBase() {
	return;
}


void SceneBase::update(float dt) {
	frame_time	+= dt;
	frame_count	+= 1.0f;

	if ((timeout += dt) >= 1.0f) {
		std::stringstream ss;
		ss.flags(std::stringstream::fixed);
		ss.precision(2);
		ss << (frame_count / frame_time) << std::endl;
		ss << (frame_time / frame_count * 1000) << "ms" << std::endl;
		fps_label->setText(ss.str());

		frame_count	= 0.0f;
		frame_time	= 0.0f;
		timeout		= 0.0f;
	}

	return;
}


void SceneBase::onViewportChanged(const rectangle& old_viewport, const rectangle& new_viewport) {
	Viewport::onViewportChanged(old_viewport, new_viewport);
	float scale = 1.0f / this->getLocalTransform().m11;

	if (bt_back) {
		bt_back->setPosition(0, new_viewport.getMaxY());
		bt_back->setScale(scale);
	}

	// update the scale of the FPS label to keep the same size for all scenes
	fps_label->setScale(scale);

	return;
}


void SceneBase::onButtonBack(Button* button) {
	assert(this->bt_back == button);
	assert(this->previous);

	// keep the object alive until the object ends
	wiesel::ref<SceneBase> local_ref(this);

	// replace the active scene
	getApplication()->clearSceneStack();
	getApplication()->pushScene(previous);

	// unregister updates from the current scene, re-add the previous one
	Engine::getInstance()->unregisterUpdateable(this);
	Engine::getInstance()->registerUpdateable(previous);

	local_ref = NULL;

	return;
}

