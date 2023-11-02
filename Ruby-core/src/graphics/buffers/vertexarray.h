#pragma once

#include <gl/glew.h>
#include <vector>
#include "buffer.h"

namespace Ruby { namespace Graphics {

	class VertexArray
	{
	private:
		GLuint m_ArrayID;
		std::vector<Buffer*> m_Buffers;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer* buffer, GLuint index);
		void bind() const;
		void unbind() const;
	};
}}