#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "Shader.h"

#include "../maths/maths.h"

namespace Ruby { namespace Graphics {

	class Renderable2d
	{
	protected:
		Maths::vec3 m_Position;
		Maths::vec2 m_Size;
		Maths::vec4 m_Color;

		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
		Shader& m_Shader;
	public:
		Renderable2d(Maths::vec3 position, Maths::vec2 size, Maths::vec4 color,Shader& shader)
			:m_Position(position),m_Size(size),m_Color(color),m_Shader(shader)
		{
			m_VertexArray = new VertexArray();

			GLfloat vertices[] =
			{
				0,0,0,
				0,size.y,0,
				size.x,size.y,0,
				size.x,0,0
			};

			GLfloat colors[] =
			{
				color.x,color.y,color.z,color.w,
				color.x,color.y,color.z,color.w,
				color.x,color.y,color.z,color.w,
				color.x,color.y,color.z,color.w  
			};

			m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

			GLushort indices[] = { 0,1,2,2,3,0 };
			m_IndexBuffer = new IndexBuffer(indices, 6);
		}

		virtual ~Renderable2d()
		{
			delete m_VertexArray;
			delete m_IndexBuffer;
		}

		inline const Maths::vec3& getPosition() const { return m_Position; }
		inline const Maths::vec2& getSize() const { return m_Size; }
		inline const Maths::vec4& getColor() const { return m_Color; }

		inline const VertexArray* getVAO() const { return m_VertexArray; }
		inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
		inline Shader& getShader() const { return m_Shader; }
	};
}}