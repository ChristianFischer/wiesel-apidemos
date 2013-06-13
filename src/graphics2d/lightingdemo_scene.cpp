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
#include "lightingdemo_scene.h"
#include "wiesel/video/shader_builder.h"

#include <wiesel/graph/2d/rect_shape_node.h>
#include <wiesel/graph/lighting/lighting_manager_builder.h>
#include <wiesel/io/filesystem.h>
#include <wiesel/ui/touchhandler.h>
#include <wiesel/video/shaders.h>
#include <wiesel/video/texture.h>

#include <sstream>

using namespace wiesel;
using namespace wiesel::video;

#define SIZE 4


LightingDemoScene::LightingDemoScene(ApiDemosApp *app, SceneBase *previous)
	:	SceneBase(app, previous)
{
	loadLightingManager();

	File*			sprite_file		= Engine::getInstance()->getAssetFileSystem()->findFile("/images/brickwall.png");
	Texture*		sprite_texture	= Texture::fromFile(sprite_file);

	sprite_texture->loadContentFrom(app->getScreen());
	SpriteFrame*	sprite_frame	= new SpriteFrame("brickwall", sprite_texture);
	dimension		sprite_size		= sprite_texture->getOriginalSize();

	multisprite = new MultiSpriteNode(sprite_texture);
	multisprite->setPivot(0.5f, 0.5f);
	lighting_manager->addTarget(multisprite);
	lighting_manager->addChild(multisprite);

	for(int x=0; x<SIZE; x++) {
		for(int y=0; y<SIZE; y++) {
			multisprite->addSprite(
							sprite_frame,
							vector2d(
									x * sprite_size.width,
									y * sprite_size.height
							)
			);
		}
	}

	content_size = dimension(sprite_size.width*SIZE, sprite_size.height*SIZE);

	this->setScaleMode(
			Viewport::FitToParent,
			dimension(sprite_size.width*SIZE, sprite_size.height*SIZE)
	);

	return;
}


LightingDemoScene::~LightingDemoScene() {
}


void LightingDemoScene::update(float dt) {
	SceneBase::update(dt);

	return;
}


void LightingDemoScene::onViewportChanged(const rectangle& old_viewport, const rectangle& new_viewport) {
	SceneBase::onViewportChanged(old_viewport, new_viewport);

	multisprite->setPosition(
						new_viewport.size.width  / 2,
						new_viewport.size.height / 2
	);

	return;
}


void LightingDemoScene::onTouchStarted(wiesel::Touch *touch) {
	if (touch->getTouchID() < lighting_manager->getMaxLightSources()) {
		touch->claim(this);

		LightsPerTouchMap::iterator active_light_it = lights.find(touch->getTouchID());
		LightNode2D *light_node = NULL;

		if (active_light_it == lights.end()) {
			light_node = new LightNode2D();
			light_node->setLightZPosition(20.0f);
			light_node->setLightStrength(10.0f);
			multisprite->addChild(light_node);

			// set the light's color based on their touch ID
			switch(touch->getTouchID()) {
				case 0:		light_node->setLightColorDiffuse(1.0f, 0.8f, 0.5f);		break;
				case 1:		light_node->setLightColorDiffuse(0.5f, 0.5f, 1.0f);		break;
				case 2:		light_node->setLightColorDiffuse(0.5f, 1.0f, 0.5f);		break;
				case 3:		light_node->setLightColorDiffuse(0.8f, 0.5f, 1.0f);		break;
				case 4:		light_node->setLightColorDiffuse(1.0f, 1.0f, 0.5f);		break;
				case 5:		light_node->setLightColorDiffuse(1.0f, 0.5f, 1.0f);		break;
				case 6:		light_node->setLightColorDiffuse(0.5f, 1.0f, 1.0f);		break;
				case 7:		light_node->setLightColorDiffuse(0.5f, 0.8f, 1.0f);		break;
				default:	light_node->setLightColorDiffuse(1.0f, 1.0f, 1.0f);		break;
			}

			// the light also needs to be added to the lighting manager
			lighting_manager->addLightSource(light_node);
			lights[touch->getTouchID()] = light_node;
		}
		else {
			light_node = active_light_it->second;
			light_node->setLightEnabled(true);
		}

		// update the light's position
		light_node->setPosition(multisprite->convertWorldToLocal(touch->getScreenLocation()));

		// get the highest active touch
		const TouchList* touches = getApplication()->getScreen()->getTouchHandler()->getActiveTouches();
		TouchID highest_active_touch = 0;

		for(TouchList::const_iterator it=touches->begin(); it!=touches->end(); it++) {
			if ((*it)->getOwner() == this && ((*it)->getState() != TouchState_Released)) {
				highest_active_touch = std::max(highest_active_touch, (*it)->getTouchID());
			}
		}

		// disable all lights with inactive touches
		for(LightsPerTouchMap::iterator it=lights.begin(); it!=lights.end(); it++) {
			if (it->first > highest_active_touch) {
				it->second->setLightEnabled(false);
			}
		}
	}

	return;
}


void LightingDemoScene::onTouchMoved(const wiesel::Touch *touch) {
	LightsPerTouchMap::iterator active_light_it = lights.find(touch->getTouchID());
	if (active_light_it != lights.end()) {
		active_light_it->second->setPosition(multisprite->convertWorldToLocal(touch->getScreenLocation()));
	}

	return;
}


void LightingDemoScene::onTouchEnded(const wiesel::Touch *touch) {
	return;
}


void LightingDemoScene::loadLightingManager() {
	ShaderBuilder shader_builder;
	shader_builder.setSourcesFromFiles(Engine::getInstance()->getAssetFileSystem(), "/shaders/2dlighting");

	shader_builder.setDefaultAttributeName(Shader::VertexPosition,			0);
	shader_builder.setDefaultAttributeName(Shader::Texture,					0);
	shader_builder.setDefaultAttributeName(Shader::VertexTextureCoordinate,	0);

	shader_builder.addDefaultModelviewMatrixConstantBuffer();
	shader_builder.addDefaultProjectionMatrixConstantBuffer();

	LightingManagerBuilder lighting_builder;
	lighting_builder.setMaxLightSources(4);
	lighting_builder.setConstantBufferName("light_info");
	lighting_builder.setLightsUniformName("lights");
	lighting_builder.setLightsCountUniformName("lights_count");
	lighting_builder.addDefaultLightInfoMember(LightSource::Attribute_Position);
	lighting_builder.addDefaultLightInfoMember(LightSource::Attribute_ColorDiffuse);
	lighting_builder.addDefaultLightInfoMember(LightSource::Attribute_Strength);
	this->lighting_manager = lighting_builder.create();

	shader_builder.addConstantBuffer(
						lighting_manager->getConstantBufferName(),
						Shader::Context_FragmentShader,
						lighting_manager->getConstantBufferTemplate()
	);

	lighting_manager->setDefaultLightingShader(shader_builder.create());
	this->addChild(lighting_manager);

	return;
}
