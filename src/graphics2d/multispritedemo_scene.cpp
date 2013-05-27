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
#include "multispritedemo_scene.h"
#include "wiesel/io/filesystem.h"

#include <wiesel/video/texture.h>

using namespace wiesel;
using namespace wiesel::video;

#define SIZE 32


MultiSpriteDemoScene::MultiSpriteDemoScene(ApiDemosApp *app, SceneBase *previous)
	:	SceneBase(app, previous)
{
	File*			sprite_file		= Engine::getInstance()->getAssetFileSystem()->findFile("/images/wiesel.png");
	Texture*		sprite_texture	= Texture::fromFile(sprite_file);

	sprite_texture->loadContentFrom(app->getScreen());
	SpriteFrame*	sprite_frame	= new SpriteFrame("wiesel", sprite_texture);
	dimension		sprite_size		= sprite_texture->getOriginalSize();

	multisprite = new MultiSpriteNode(sprite_texture);
	multisprite->setPivot(0.5f, 0.5f);
	this->addChild(multisprite);

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
	rotation = 0.0f;

	this->setScaleMode(
			Viewport::FitToParent,
			dimension(sprite_size.width*SIZE, sprite_size.height*SIZE)
	);

	return;
}


MultiSpriteDemoScene::~MultiSpriteDemoScene() {
}


void MultiSpriteDemoScene::update(float dt) {
	SceneBase::update(dt);

	if((rotation += (45.0f * dt)) > 360.0f) {
		rotation -= 360.0f;
	}

	multisprite->setRotation(rotation);

	return;
}


void MultiSpriteDemoScene::onViewportChanged(const rectangle& old_viewport, const rectangle& new_viewport) {
	SceneBase::onViewportChanged(old_viewport, new_viewport);

	multisprite->setPosition(
						new_viewport.size.width  / 2,
						new_viewport.size.height / 2
	);

	return;
}

