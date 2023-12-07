#include "sprite.h"

namespace Ruby { namespace Graphics {
	Sprite::Sprite(float x, float y, float width, float height, const Maths::vec4& color)
		:Renderable2d(Maths::vec3(x, y, 0), Maths::vec2(width, height), color)
	{

	}
	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		:Renderable2d(Maths::vec3(x, y, 0), Maths::vec2(width, height), Maths::vec4(1,0,1,1))
	{
		m_Texture = texture;
	}
}}