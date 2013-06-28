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
#include "multitexturedemo_scene.h"

#include <wiesel/io/filesystem.h>
#include <wiesel/video/render_context.h>
#include <wiesel/video/shader_builder.h>
#include <wiesel/video/texture.h>

using namespace wiesel;
using namespace wiesel::video;




class MultiTextureDemo : public Node2D, public MultiTextureTarget, public ShaderTarget
{
public:
	MultiTextureDemo(ApiDemosApp *app) {
		File*		wall_file		= Engine::getInstance()->getAssetFileSystem()->findFile("/images/brickwall.png");
		Texture*	wall_texture	= Texture::fromFile(wall_file);
		wall_texture->loadContentFrom(app->getScreen());
		setTexture(0, wall_texture);

		File*		noise_file		= Engine::getInstance()->getAssetFileSystem()->findFile("/images/noise.png");
		Texture*	noise_texture	= Texture::fromFile(noise_file);
		noise_texture->loadContentFrom(app->getScreen());
		setTexture(1, noise_texture);

		vbo = new VertexBuffer();
		vbo->clear();
		vbo->setupVertexPositions(2);
		vbo->setupTextureLayer(0);
		vbo->addVertex(  0, 100);
		vbo->addVertex(  0,   0);
		vbo->addVertex(100, 100);
		vbo->addVertex(100,   0);

		vbo->setVertexTextureCoordinate(0,  0.0f,  0.0f);
		vbo->setVertexTextureCoordinate(1,  0.0f, 4.0f);
		vbo->setVertexTextureCoordinate(2, 4.0f,  0.0f);
		vbo->setVertexTextureCoordinate(3, 4.0f, 4.0f);

		ShaderBuilder shader_builder;
		shader_builder.setSourcesFromFiles(Engine::getInstance()->getAssetFileSystem(), "/shaders/multi_texture_demo");

		shader_builder.setDefaultAttributeName(Shader::VertexPosition,			0);
		shader_builder.setDefaultAttributeName(Shader::Texture,					0);
		shader_builder.setDefaultAttributeName(Shader::Texture,					1);
		shader_builder.setDefaultAttributeName(Shader::VertexTextureCoordinate,	0);
		shader_builder.setDefaultAttributeName(Shader::VertexTextureCoordinate,	1);

		shader_builder.addDefaultModelviewMatrixConstantBuffer();
		shader_builder.addDefaultProjectionMatrixConstantBuffer();

		this->setShader(shader_builder.create());

		return;
	}

	virtual ~MultiTextureDemo() {
		return;
	}


	virtual void onDraw(video::RenderContext *render_context) {
		this->applyShaderConfigTo(render_context);
		this->applyTextureConfigTo(render_context);

		render_context->setModelviewMatrix(getWorldTransform());
		render_context->draw(video::TriangleStrip, vbo);

		return;
	}


// MultiTextureTarget
public:
	virtual uint16_t getTextureLayersMax() const {
		return 2;
	}


private:
	wiesel::ref<VertexBuffer>	vbo;
};





MultiTextureDemoScene::MultiTextureDemoScene(ApiDemosApp *app, SceneBase *previous)
	:	SceneBase(app, previous)
{
	this->setScaleMode(
			Viewport::FitToParent,
			dimension(100, 100)
	);

	Viewport* vp = new Viewport();
	this->addChild(vp);
	vp->setScaleMode(
				Viewport::ScaleByWidthOrHeight,
				dimension(100, 100),
				vector2d(0.5f, 0.5f)
	);

	this->node = new MultiTextureDemo(app);
	this->node->setPosition(0.0f, 0.0f);
	vp->addChild(node);

	return;
}


MultiTextureDemoScene::~MultiTextureDemoScene() {
}


void MultiTextureDemoScene::update(float dt) {
	SceneBase::update(dt);

	return;
}


void MultiTextureDemoScene::onViewportChanged(const rectangle& old_viewport, const rectangle& new_viewport) {
	SceneBase::onViewportChanged(old_viewport, new_viewport);

	/*
	node->setPosition(
						(new_viewport.size.width  / 2),
						(new_viewport.size.height / 2)
	);
	*/

	return;
}

