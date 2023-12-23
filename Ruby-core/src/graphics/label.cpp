#include "label.h"

namespace Ruby {
	namespace Graphics {
		Label::Label(std::string text, float x, float y, Maths::vec4 color)
			:Renderable2d(), text(text), position(m_Position)
		{
			m_Position= Maths::vec3(x, y, 0.0f);
			m_Color = color;
		}
		void Label::submit(Renderer2d* renderer) const
		{
			renderer->drawString(text, position, m_Color);
		}
	}
}