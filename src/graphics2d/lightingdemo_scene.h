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
#ifndef __GRAPHICS2D_LIGHTINGDEMO_SCENE_H__
#define __GRAPHICS2D_LIGHTINGDEMO_SCENE_H__

#include "../scene_base.h"

#include <wiesel/graph/2d/sprite_node.h>
#include <wiesel/graph/lighting/light_node_2d.h>
#include <wiesel/graph/lighting/light_source.h>
#include <wiesel/graph/lighting/lighting_manager.h>
#include <wiesel/ui/touch.h>
#include <vector>


class LightingDemoScene :
		public SceneBase,
		public wiesel::TouchReceiver
{
public:
	LightingDemoScene(ApiDemosApp *app, SceneBase *previous);
	virtual ~LightingDemoScene();

public:
	virtual void update(float dt);

protected:
	virtual void onViewportChanged(const wiesel::rectangle& old_viewport, const wiesel::rectangle& new_viewport);

public:
	virtual void onTouchStarted(wiesel::Touch *touch);
	virtual void onTouchMoved(const wiesel::Touch *touch);
	virtual void onTouchEnded(const wiesel::Touch *touch);

private:
	void loadLightingManager();

private:
	typedef std::map<wiesel::TouchID,wiesel::LightNode2D*>	LightsPerTouchMap;

	wiesel::ref<wiesel::MultiSpriteNode>			multisprite;
	wiesel::ref<wiesel::LightingManager>			lighting_manager;
	wiesel::dimension								content_size;
	LightsPerTouchMap								lights;
};

#endif // __GRAPHICS2D_LIGHTINGDEMO_SCENE_H__
