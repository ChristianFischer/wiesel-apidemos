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
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <wiesel/graph/2d/sprite_node.h>
#include <wiesel/resources/graphics/spriteframe.h>
#include <wiesel/ui/touch.h>


class Button : 
	public wiesel::SpriteNode,
	public wiesel::TouchReceiver
{
public:
	typedef void (wiesel::Node::*OnButtonClicked)(Button *button);

public:
	Button(
			wiesel::SpriteFrame *frame, wiesel::SpriteFrame *frame_selected,
			wiesel::Node *cb_obj, OnButtonClicked cb_func
	);
	virtual ~Button();

// TouchReceiver
public:
	virtual void onTouchStarted(wiesel::Touch *touch);
	virtual void onTouchMoved(const wiesel::Touch *touch);
	virtual void onTouchEnded(const wiesel::Touch *touch);

private:
	wiesel::ref<wiesel::SpriteFrame>	frame;
	wiesel::ref<wiesel::SpriteFrame>	frame_selected;

	wiesel::Node*						cb_obj;
	OnButtonClicked						cb_func;
};

#endif // __BUTTON_H__
