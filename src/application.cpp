/**
 * Copyright (C) 2012
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
#include <wiesel/io/filesystem.h>
#include <wiesel/resources/graphics/spritesheet.h>
#include <wiesel/ui/bitmapfont.h>
#include <wiesel/video/render_context.h>
#include <wiesel/video/screen.h>
#include <wiesel/video/texture.h>
#include <wiesel/video/video_driver.h>
#include <wiesel/application_main.h>
#include <wiesel.h>

#include "application.h"

using namespace wiesel;
using namespace wiesel::video;
using namespace std;


MyApplication::MyApplication() {
}

MyApplication::~MyApplication() {
}


bool MyApplication::onInit() {
	// at first, we create our screen object
	screen = new Screen();

	// the screen needs to be initialized
	screen->loadVideoDevice(dimension(640, 480), 0);

	// successful?
	assert(screen->getVideoDeviceDriver());
	if (!screen->getVideoDeviceDriver()) {
		return false;
	}

	// print video information
	Log::info << *(screen->getVideoDeviceDriver()->getVideoInfo()) << std::endl;

	// load the bitmap font
	File*			font_file		= Engine::getInstance()->getAssetFileSystem()->findFile("/images/font.png");
	Texture*		font_texture	= Texture::fromFile(font_file);
	SpriteSheet*	font_ss			= new SpriteSheet(font_texture);

	// prepare the texture
	font_texture->loadContentFrom(screen);

	// configure the font
	font_ss->createRasterFrames(16, 8,  0, 26, 'A');
	font_ss->createRasterFrames(16, 8, 32, 26, 'a');
	font_ss->createRasterFrames(16, 8, 97, 31, '!');
	this->default_font = new BitmapFont(font_ss);

	// create a scene which will be rendered to our screen
	Scene *scene = new Scene();
	pushScene(scene);

	return true;
}


void MyApplication::onRun(float dt) {
	Application::onRun(dt);

	switch(screen->getState()) {
		case Video_Uninitialized: {
			// do nothing
			break;
		}

		case Video_Suspended: {
			// do nothing
			// in this state, the application is disabled in the background
			// and not visible on the screen.
			// for example: on android or iOS another app is currently running.
			break;
		}

		case Video_Background:
		case Video_Active: {
			// render the screen content, when the window is either active in the foreground
			// or inactive (but visible) in the background
			if (screen && screen->getVideoDeviceDriver()) {
				screen->getVideoDeviceDriver()->preRender();
				this->onRender(screen->getVideoDeviceDriver()->getCurrentRenderContext());
				screen->getVideoDeviceDriver()->postRender();
			}

			break;
		}
	}

	return;
}


void MyApplication::onRender(RenderContext *render_context) {
	Application::onRender(render_context);
	return;
}


void MyApplication::onShutdown() {
	return;
}



// set the application entry point
WIESEL_APPLICATION_SETUP( MyApplication );


