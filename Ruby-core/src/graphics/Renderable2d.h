#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "Shader.h"
#include "renderer2d.h"
#include "../graphics/texture.h"

#include "../maths/maths.h"

namespace Ruby {
	namespace Graphics {

		struct VertexData
		{
			Maths::vec3 vertex;
			Maths::vec2 uv;
			float tid;
			unsigned int color;
		};

		class Renderable2d
		{
		protected:
			Maths::vec3 m_Position;
			Maths::vec2 m_Size;
			Maths::vec4 m_Color;
			std::vector<Maths::vec2> m_UV;
			Ruby::Graphics::Texture* m_Texture;
		protected:
			Renderable2d() 
			{
				setUVDefaults();
			}
		public:
			Renderable2d(Maths::vec3 position, Maths::vec2 size, Maths::vec4 color)
				:m_Position(position), m_Size(size), m_Color(color)
			{
				setUVDefaults();
			}

			virtual ~Renderable2d() {}

			virtual void submit(Renderer2d* renderer) const
			{
				renderer->submit(this);
			}

			inline const Maths::vec3& getPosition() const { return m_Position; }
			inline const Maths::vec2& getSize() const { return m_Size; }
			inline const Maths::vec4& getColor() const { return m_Color; }
			inline const std::vector<Maths::vec2>& getUV() const { return m_UV; }
			inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }
		private:
			void setUVDefaults()
			{
				m_UV.push_back(Maths::vec2(0, 0));
				m_UV.push_back(Maths::vec2(0, 1));
				m_UV.push_back(Maths::vec2(1, 1));
				m_UV.push_back(Maths::vec2(1, 0));
			}
		};
	}
}