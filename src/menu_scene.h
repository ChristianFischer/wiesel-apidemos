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
#ifndef __MENUSCENE_H__
#define __MENUSCENE_H__

#include "scene_base.h"

#include <wiesel/graph/2d/rect_shape_node.h>
#include <wiesel/ui/touch.h>
#include <list>



template<class SCENE>
wiesel::Scene* createScene(ApiDemosApp* app, SceneBase* previous) {
	return new SCENE(app, previous);
}



class MenuScene :
	public SceneBase,
	public wiesel::TouchReceiver
{
public:
	MenuScene(ApiDemosApp *app, SceneBase *previous);
	virtual ~MenuScene();

public:
	typedef wiesel::Scene* (*SceneFactory)(ApiDemosApp* app, SceneBase* previous);

	struct MenuItem {
		std::string					title;
		wiesel::RectShapeNode*		node;
		SceneFactory				factory;
	};

public:
	void addMenuEntry(const std::string& title, SceneFactory factory);

protected:
	virtual void onViewportChanged(const wiesel::rectangle& old_viewport, const wiesel::rectangle& new_viewport);

// TouchReceiver
public:
	virtual void onTouchStarted(wiesel::Touch *touch);
	virtual void onTouchMoved(const wiesel::Touch *touch);
	virtual void onTouchEnded(const wiesel::Touch *touch);

private:
	float clipScrollOffset(float offset);

private:
	wiesel::ref<wiesel::Node2D>		scroll_node;
	wiesel::ref<wiesel::Node2D>		scroll_offset_node;

	std::list<MenuItem>				menu_item_list;
	MenuItem*						selected_item;

	float							total_height;
	float							scroll_offset;
};

#endif // __MENUSCENE_H__

