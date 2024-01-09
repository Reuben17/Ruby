#pragma once

#include <iostream>
#include <vector>

#ifdef RUBY_EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif // RUBY_EMSCRITPEN

#include "../Maths/Maths.h"
#include "../utils/fileutils.h"

namespace Ruby {
	namespace Graphics {

		class Shader
		{
		private:
			
			const char* m_VertPath;
			const char* m_FragPath;
		public:
			GLuint m_ShaderID;
			Shader(const char* vertPath, const char* fragPath);
			~Shader();


			void setUniform1f(const GLchar* name, float value);
			void setUniform1fv(const GLchar* name, float * value, int count);
			void setUniform1i(const GLchar* name, int value);
			void setUniform1iv(const GLchar* name, int* value, int count);
			void setUniform2f(const GLchar* name, const Maths::vec2& vector);
			void setUniform3f(const GLchar* name, const Maths::vec3& vector);
			void setUniform4f(const GLchar* name, const Maths::vec4& vector);
			void setUniformMat4(const GLchar* name, const Maths::mat4& matrix);

			void enable() const;
			void disable() const;
		private:
			GLuint load();
			GLint getUniformLocation(const GLchar* name);
		};

	}
}