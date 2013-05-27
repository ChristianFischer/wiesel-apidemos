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
#include "button.h"

using namespace wiesel;


Button::Button(
			SpriteFrame *frame, SpriteFrame *frame_selected,
			Node *cb_obj, OnButtonClicked cb_func
) : SpriteNode(frame) {
	this->frame				= frame;
	this->frame_selected	= frame_selected;
	this->cb_obj			= cb_obj;
	this->cb_func			= cb_func;

	return;
}


Button::~Button() {
}


void Button::onTouchStarted(wiesel::Touch *touch) {
	if (touch->getTouchID() == 0) {
		vector2d nodespace = convertWorldToLocal(touch->getScreenLocation());

		if (hitBy(nodespace)) {
			this->setSpriteFrame(frame_selected);
			touch->claim(this);
		}
	}

	return;
}


void Button::onTouchMoved(const wiesel::Touch *touch) {
	return;
}


void Button::onTouchEnded(const wiesel::Touch *touch) {
	if (touch->getTouchID() == 0) {
		vector2d nodespace = convertWorldToLocal(touch->getScreenLocation());

		if (hitBy(nodespace)) {
			if (cb_obj && cb_func) {
				(cb_obj->*cb_func)(this);
			}
		}

		this->setSpriteFrame(frame);
	}

	return;
}

