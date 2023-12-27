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
			unsigned int m_Color;
			std::vector<Maths::vec2> m_UV;
			Ruby::Graphics::Texture* m_Texture;
		protected:
			Renderable2d() 
				:m_Texture(nullptr)
			{
				setUVDefaults();
			}
		public:
			Renderable2d(Maths::vec3 position, Maths::vec2 size, unsigned int color)
				:m_Position(position), m_Size(size), m_Color(color),m_Texture(nullptr)
			{
				setUVDefaults();
			}

			virtual ~Renderable2d() {}

			virtual void submit(Renderer2d* renderer) const
			{
				renderer->submit(this);
			}

			void setColor(unsigned int color) { m_Color = color; }
			void setColor(const Maths::vec4& color)
			{
				int r = (color.x * 255.0f);
				int g = (color.y * 255.0f);
				int b = (color.z * 255.0f);
				int a = (color.w * 255.0f);

				m_Color = a << 24 | b << 16 | g << 8 | r;
			}

			inline const Maths::vec3& getPosition() const { return m_Position; }
			inline const Maths::vec2& getSize() const { return m_Size; }
			inline const unsigned int getColor() const { return m_Color; }
			inline const std::vector<Maths::vec2>& getUV() const { return m_UV; }
			inline const GLuint getTID() const { return m_Texture ?  m_Texture->getID(): 0; }
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