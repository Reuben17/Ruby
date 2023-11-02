#pragma once

#include <gl/glew.h>

namespace Ruby { namespace Graphics {

		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_Count;
		public:
			IndexBuffer(GLushort* data, GLuint count);

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return m_Count; }
		};

}}
