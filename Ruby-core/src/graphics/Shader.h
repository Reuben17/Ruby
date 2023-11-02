#pragma once

#include <GL/glew.h>
#include "../utils/fileutils.h"
#include "../maths/maths.h"
#include <vector>
#include <iostream>

namespace Ruby{ namespace Graphics{

	class Shader
	{
	private:
		GLuint m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void setUniform1i(const char* name, int value);
		void setUniform1f(const char* name, float value);
		void setUniform2f(const char* name, const Maths::vec2& vector);
		void setUniform3f(const char* name, const Maths::vec3& vector);
		void setUniform4f(const char* name, const Maths::vec4& vector);
		void setUniformMat4(const char* name, const Maths::mat4& matrix);

		void enable() const;
		void disable() const;
	private:
		GLuint load();
		GLint getUniformLocation(const GLchar* name);
	};

} }