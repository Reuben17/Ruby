#pragma once

#include "Renderable2d.h"

namespace Ruby { namespace Graphics {

	class Sprite : public Renderable2d
	{
	public:
		Maths::vec3& position;
	public:
		Sprite(float x, float y, float width, float height, unsigned int color);
		Sprite(float x, float y, float width, float height, Texture* texture);
	};

}}