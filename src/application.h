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
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <wiesel/application.h>

#include <wiesel/ui/font.h>


class MyApplication : public wiesel::Application
{
public:
	MyApplication();
	virtual ~MyApplication();

public:
	virtual bool onInit();
	virtual void onRun(float dt);
	virtual void onRender(wiesel::video::RenderContext *render_context);
	virtual void onShutdown();

public:
	inline wiesel::video::Screen* getScreen() {
		return screen;
	}

	inline wiesel::Font* getDefaultFont() {
		return default_font;
	}

private:
	wiesel::ref<wiesel::video::Screen>		screen;
	wiesel::ref<wiesel::Font>				default_font;
};

#endif // __APPLICATION_H__

