#pragma once
#include "Renderable2d.h"

namespace Ruby {
	namespace Graphics {
		class Label: public Renderable2d
		{
		public:
			Label(std::string text,float x,float y,Maths::vec4 color);
			void submit(Renderer2d* renderer) const override;
		public:
			std::string text;
			Maths::vec3& position;
			float x, y;
		};
	}
}