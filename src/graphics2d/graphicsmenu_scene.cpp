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
#include "graphicsmenu_scene.h"

#include "spritedemo_scene.h"
#include "multispritedemo_scene.h"
#include "multitexturedemo_scene.h"
#include "shaderdemo_scene.h"
#include "mandelbrotdemo_scene.h"
#include "lightingdemo_scene.h"


Graphics2DMenuScene::Graphics2DMenuScene(ApiDemosApp* app, SceneBase *previous) : MenuScene(app, previous) {
	this->addMenuEntry("1.024 single sprites",		&createScene<SpriteDemoScene>);
	this->addMenuEntry("1.024 batch frames",		&createScene<MultiSpriteDemoScene>);
	this->addMenuEntry("multitexture demo",			&createScene<MultiTextureDemoScene>);
	this->addMenuEntry("shader effects",			&createScene<ShaderDemoScene>);
	this->addMenuEntry("Mandelbrot shader",			&createScene<MandelbrotDemoScene>);
	this->addMenuEntry("lighting",					&createScene<LightingDemoScene>);

	return;
}

Graphics2DMenuScene::~Graphics2DMenuScene() {
}

