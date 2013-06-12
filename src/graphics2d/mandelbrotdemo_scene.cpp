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
#include "mandelbrotdemo_scene.h"
#include "wiesel/io/filesystem.h"
#include "wiesel/graph/2d/rect_shape_node.h"
#include "wiesel/video/shaders.h"
#include "wiesel/video/shader_builder.h"

#include <wiesel/video/texture.h>

using namespace wiesel;
using namespace wiesel::video;


MandelbrotDemoScene::MandelbrotDemoScene(ApiDemosApp *app, SceneBase *previous)
	:	SceneBase(app, previous)
{
	shift = vector2d(0.5f, 0.0f);

	ShaderBuilder shader_builder;
	shader_builder.setSourcesFromFiles(Engine::getInstance()->getAssetFileSystem(), "/shaders/mandelbrot");

	shader_builder.setDefaultAttributeName(Shader::VertexPosition,		0);
	shader_builder.setDefaultAttributeName(Shader::VertexColor,			0);

	shader_builder.addDefaultModelviewMatrixConstantBuffer();
	shader_builder.addDefaultProjectionMatrixConstantBuffer();

	rect_node = new RectShapeNode();
	rect_node->setPivot(0, 0);
	rect_node->setPosition(0, 0);
	rect_node->setShader(shader_builder.create());

	this->addChild(rect_node);

	return;
}


MandelbrotDemoScene::~MandelbrotDemoScene() {
}


void MandelbrotDemoScene::update(float dt) {
	SceneBase::update(dt);

	return;
}


void MandelbrotDemoScene::onViewportChanged(const rectangle& old_viewport, const rectangle& new_viewport) {
	SceneBase::onViewportChanged(old_viewport, new_viewport);
	rect_node->setRect(new_viewport);

	updateMandelbrotView();

	return;
}


void MandelbrotDemoScene::onTouchStarted(Touch* touch) {
	if (touch->getTouchID() == 0) {
		touch->claim(this);
	}

	return;
}


void MandelbrotDemoScene::onTouchMoved(const Touch* touch) {
	if (touch->getTouchID() == 0) {
		vector2d moved = (touch->getScreenLocation() - touch->getPreviousScreenLocation());
		float max_size = getViewport().size.getMax();
		shift.x += 2.0f * moved.x / max_size;
		shift.y += 2.0f * moved.y / max_size;

		updateMandelbrotView();
	}

	return;
}


void MandelbrotDemoScene::onTouchEnded(const Touch* touch) {
	if (touch->getTouchID() == 0) {
	}

	return;
}


void MandelbrotDemoScene::updateMandelbrotView() {
	float aspect_ratio = this->getViewport().size.getRatio();
	float top, left, right, bottom;

	if (aspect_ratio > 1.0f) {
		left   = -1.0f;
		right  = +1.0f;
		top    = -(1.0f / aspect_ratio);
		bottom = +(1.0f / aspect_ratio);
	}
	else {
		top    = -1.0f;
		bottom = +1.0f;
		left   = -(1.0f * aspect_ratio);
		right  = +(1.0f * aspect_ratio);
	}

	top    += shift.y;
	left   -= shift.x;
	right  -= shift.x;
	bottom += shift.y;

	rect_node->setColorBottomLeft  (left,  bottom, 0.0f);
	rect_node->setColorBottomRight (right, bottom, 0.0f);
	rect_node->setColorTopLeft     (left,  top,    0.0f);
	rect_node->setColorTopRight    (right, top,    0.0f);

	return;
}
