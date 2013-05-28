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
#ifndef __GRAPHICS2D_SHADERDEMO_SCENE_H__
#define __GRAPHICS2D_SHADERDEMO_SCENE_H__

#include "../scene_base.h"

#include <wiesel/graph/2d/sprite_node.h>
#include <wiesel/ui/label_node.h>
#include <wiesel/video/shader.h>
#include <string>
#include <vector>


class ShaderDemoScene : public SceneBase
{
public:
	ShaderDemoScene(ApiDemosApp *app, SceneBase *previous);
	virtual ~ShaderDemoScene();

public:
	virtual void update(float dt);

protected:
	virtual void onViewportChanged(const wiesel::rectangle& old_viewport, const wiesel::rectangle& new_viewport);

private:
	void onButtonPrevious(Button *button);
	void onButtonNext(Button *button);

	void setNextShader(int index);

private:
	struct ShaderEntry {
		std::string								name;
		wiesel::ref<wiesel::video::Shader>		shader;
	};

	wiesel::ref<wiesel::SpriteNode>		sprite;
	wiesel::ref<wiesel::Node2D>			hud_node;
	wiesel::ref<wiesel::LabelNode>		shader_label;
	std::vector<ShaderEntry>			shaders;
	int									current_shader;
};

#endif // __GRAPHICS2D_SHADERDEMO_SCENE_H__
