#pragma once
#include "Renderable2d.h"
#include "FontManager.h"

namespace Ruby {
	namespace Graphics {
		class Label: public Renderable2d
		{
		public:
			Label(std::string text, float x, float y,unsigned int color);
			Label(std::string text,float x,float y,Font* font ,unsigned int color);
			Label(std::string text, float x, float y, const std::string& font, unsigned int color);
			Label(std::string text, float x, float y, const std::string& font,unsigned int size, unsigned int color);
			void submit(Renderer2d* renderer) const override;
			void validateFont(const std::string& name, int size =-1);
		public:
			Font* m_Font;
			std::string text;
			Maths::vec3& position;
			float x, y;
		};
	}
}