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
#include "shaderdemo_scene.h"
#include "wiesel/io/filesystem.h"
#include "wiesel/video/shaders.h"
#include "wiesel/video/shader_builder.h"

#include <wiesel/video/texture.h>

#include <sstream>


using namespace wiesel;
using namespace wiesel::video;


ShaderDemoScene::ShaderDemoScene(ApiDemosApp *app, SceneBase *previous)
	:	SceneBase(app, previous)
{
	File*		sprite_file		= Engine::getInstance()->getAssetFileSystem()->findFile("/images/SAM_2694.png");
	Texture*	sprite_texture	= Texture::fromFile(sprite_file);
	sprite_texture->loadContentFrom(app->getScreen());

	sprite = new SpriteNode(sprite_texture);
	sprite->setPivot(0.5f, 0.5f);
	this->addChild(sprite);

	this->setScaleMode(
			Viewport::FitToParent,
			sprite->getContentSize()
	);

	// make default entry
	DataSource *default_glsl_vert_source
			= Engine::getInstance()->getAssetFileSystem()->findFile("/shaders/default.glsl.vert")
			->asDataSource()
	;

	std::vector<std::string> shader_names;
	shader_names.push_back("default");
	shader_names.push_back("grayscale");
	shader_names.push_back("sepia");

	for(std::vector<std::string>::iterator it=shader_names.begin(); it!=shader_names.end(); it++) {
		std::string glsl_frag_name = "/shaders/" + (*it) + ".glsl.frag";
		File *glsl_frag_file = Engine::getInstance()->getAssetFileSystem()->findFile(glsl_frag_name);

		if (glsl_frag_file == NULL) {
			continue;
		}

		ShaderBuilder shader_builder;
		shader_builder.setSource(Shader::GLSL_VERTEX_SHADER,	default_glsl_vert_source);
		shader_builder.setSource(Shader::GLSL_FRAGMENT_SHADER,	glsl_frag_file->asDataSource());

		shader_builder.setDefaultAttributeName(Shader::VertexPosition,			0);
		shader_builder.setDefaultAttributeName(Shader::Texture,					0);
		shader_builder.setDefaultAttributeName(Shader::VertexTextureCoordinate,	0);

		shader_builder.addDefaultModelviewMatrixConstantBuffer();
		shader_builder.addDefaultProjectionMatrixConstantBuffer();

		ShaderEntry entry;
		entry.name		= *it;
		entry.shader	= shader_builder.create();
		shaders.push_back(entry);
	}

	hud_node = new Node2D();
	this->addChild(hud_node);

	shader_label = new LabelNode();
	shader_label->setFont(app->getDefaultFont());
	shader_label->setPivot(0.5f, 0.5f);
	shader_label->setScale(2.0f);
	hud_node->addChild(shader_label);

	Button *bt_prev = new Button(
			getApplication()->getHudSpritesheet()->get("button_left"),
			getApplication()->getHudSpritesheet()->get("button_left_selected"),
			this, (Button::OnButtonClicked)&ShaderDemoScene::onButtonPrevious
	);
	bt_prev->setPosition(-100, 0);
	hud_node->addChild(bt_prev);

	Button *bt_next = new Button(
			getApplication()->getHudSpritesheet()->get("button_right"),
			getApplication()->getHudSpritesheet()->get("button_right_selected"),
			this, (Button::OnButtonClicked)&ShaderDemoScene::onButtonNext
	);
	bt_next->setPosition(+100, 0);
	hud_node->addChild(bt_next);

	current_shader = 0;
	setNextShader(0);

	return;
}


ShaderDemoScene::~ShaderDemoScene() {
}


void ShaderDemoScene::update(float dt) {
	SceneBase::update(dt);

	return;
}


void ShaderDemoScene::onViewportChanged(const rectangle& old_viewport, const rectangle& new_viewport) {
	SceneBase::onViewportChanged(old_viewport, new_viewport);
	float scale = 1.0f / this->getLocalTransform().m11;

	hud_node->setScale(scale);
	hud_node->setPosition(
						new_viewport.size.width  / 2,
						new_viewport.size.height / 10
	);

	sprite->setPosition(
						new_viewport.size.width  / 2,
						new_viewport.size.height / 2
	);

	return;
}


void ShaderDemoScene::onButtonPrevious(Button* button) {
	if ((--current_shader) < 0) {
		current_shader = shaders.size() - 1;
	}

	setNextShader(current_shader);

	return;
}


void ShaderDemoScene::onButtonNext(Button* button) {
	if (static_cast<size_t>(++current_shader) >= shaders.size()) {
		current_shader = 0;
	}

	setNextShader(current_shader);

	return;
}


void ShaderDemoScene::setNextShader(int index) {
	sprite->setShader(shaders[index].shader);
	shader_label->setText(shaders[index].name);
}

