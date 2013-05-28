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
#ifndef __GRAPHICS2D_MANDELBROTDEMO_SCENE_H__
#define __GRAPHICS2D_MANDELBROTDEMO_SCENE_H__

#include "../scene_base.h"

#include <wiesel/graph/2d/rect_shape_node.h>
#include <wiesel/ui/touch.h>
#include <vector>


class MandelbrotDemoScene :
		public SceneBase,
		public wiesel::TouchReceiver
{
public:
	MandelbrotDemoScene(ApiDemosApp *app, SceneBase *previous);
	virtual ~MandelbrotDemoScene();

public:
	virtual void update(float dt);

protected:
	virtual void onViewportChanged(const wiesel::rectangle& old_viewport, const wiesel::rectangle& new_viewport);

// TouchReceiver
public:
	virtual void onTouchStarted(wiesel::Touch *touch);
	virtual void onTouchMoved(const wiesel::Touch *touch);
	virtual void onTouchEnded(const wiesel::Touch *touch);

private:
	void updateMandelbrotView();

private:
	wiesel::ref<wiesel::RectShapeNode>	rect_node;
	wiesel::vector2d					shift;
};

#endif // __GRAPHICS2D_MANDELBROTDEMO_SCENE_H__
