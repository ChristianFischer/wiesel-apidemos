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
#include "spritedemo_scene.h"
#include "wiesel/io/filesystem.h"

#include <wiesel/video/texture.h>

using namespace wiesel;
using namespace wiesel::video;

#define SIZE 32


SpriteDemoScene::SpriteDemoScene(ApiDemosApp *app, SceneBase *previous)
	:	SceneBase(app, previous),
		sprites(SIZE)
{
	File*		sprite_file		= Engine::getInstance()->getAssetFileSystem()->findFile("/images/wiesel.png");
	Texture*	sprite_texture	= Texture::fromFile(sprite_file);

	sprite_texture->loadContentFrom(app->getScreen());
	dimension	sprite_size		= sprite_texture->getOriginalSize();

	offset_node = new Node2D();
	offset_node->setPivot(0, 0);
	offset_node->setPosition(0, 0);
	this->addChild(offset_node);

	for(int x=0; x<SIZE; x++) {
		for(int y=0; y<SIZE; y++) {
			SpriteNode* sprite = new SpriteNode(sprite_texture);
			sprite->setPivot(0.5f, 0.5f);
			sprite->setPosition(
						(x + 0.5f) * sprite_size.width,
						(y + 0.5f) * sprite_size.height
			);

			sprites.push_back(sprite);
			offset_node->addChild(sprite);
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


SpriteDemoScene::~SpriteDemoScene() {
}


void SpriteDemoScene::update(float dt) {
	SceneBase::update(dt);

	if((rotation += (45.0f * dt)) > 360.0f) {
		rotation -= 360.0f;
	}

	for(std::vector<wiesel::SpriteNode*>::iterator it=sprites.begin(); it!=sprites.end(); it++) {
		SpriteNode *sprite = *it;

		if (sprite) {
			sprite->setRotation(rotation);
		}
	}

	return;
}


void SpriteDemoScene::onViewportChanged(const rectangle& old_viewport, const rectangle& new_viewport) {
	SceneBase::onViewportChanged(old_viewport, new_viewport);

	offset_node->setPosition(
						(new_viewport.size.width  - content_size.width ) / 2,
						(new_viewport.size.height - content_size.height) / 2
	);

	return;
}

