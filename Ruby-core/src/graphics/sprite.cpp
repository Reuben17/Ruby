#include "sprite.h"

namespace Ruby { namespace Graphics {
	Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
		:Renderable2d(Maths::vec3(x, y, 0), Maths::vec2(width, height), color)
	{

	}
	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		:Renderable2d(Maths::vec3(x, y, 0), Maths::vec2(width, height), 0xffffffff)
	{
		m_Texture = texture;
	}
}}