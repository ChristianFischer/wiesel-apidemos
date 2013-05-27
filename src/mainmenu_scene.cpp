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
#include "mainmenu_scene.h"

#include "graphics2d/graphicsmenu_scene.h"


MainMenuScene::MainMenuScene(ApiDemosApp *app, SceneBase *previous) : MenuScene(app, previous) {
	this->addMenuEntry("Graphics - 2D",				&createScene<Graphics2DMenuScene>);

	return;
}

MainMenuScene::~MainMenuScene() {
}

