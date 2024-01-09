#pragma once

#include <vector>

#ifdef RUBY_EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif // RUBY_EMSCRITPEN

#include "buffer.h"

namespace Ruby {
	namespace Graphics {

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

	}
}