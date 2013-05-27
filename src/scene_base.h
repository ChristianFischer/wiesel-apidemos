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
#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include <wiesel/graph/scene.h>
#include <wiesel/ui/label_node.h>

#include "application.h"
#include "button.h"


class SceneBase : 
	public wiesel::Scene,
	public wiesel::IUpdateable
{
private:
	SceneBase() {}

public:
	SceneBase(ApiDemosApp *app, SceneBase *previous);
	virtual ~SceneBase();
	
public:
	inline ApiDemosApp* getApplication() {
		return app;
	}

public:
	virtual void update(float dt);

protected:
	virtual void onViewportChanged(const wiesel::rectangle& old_viewport, const wiesel::rectangle& new_viewport);

private:
	void onButtonBack(Button *button);

private:
	ApiDemosApp*						app;
	wiesel::ref<SceneBase>				previous;
	wiesel::ref<Button>					bt_back;
	wiesel::ref<wiesel::LabelNode>		fps_label;

	float								frame_count;
	float								frame_time;
	float								timeout;
};

#endif // __SCENE_BASE_H__
