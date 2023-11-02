#include "src/graphics/Window.h"
#include "src/maths/maths.h"
#include "src/graphics/Shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/Renderable2d.h"
#include "src/graphics/simple2drenderer.h"

int main(void)
{
	Ruby::Graphics::Window window("Ruby!", 960, 540);

	Ruby::Maths::mat4 ortho = Ruby::Maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Ruby::Graphics::Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", Ruby::Maths::mat4::translation(Ruby::Maths::vec3(4,3,0)));
	shader.setUniform2f("light_pos", Ruby::Maths::vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", Ruby::Maths::vec4(0.8f, 0.8f, 0.8f, 0.5f));

	Ruby::Graphics::Renderable2d sprite1(Ruby::Maths::vec3(5, 5, 0), Ruby::Maths::vec2(4, 4), Ruby::Maths::vec4(1, 0, 1, 1), shader);
	Ruby::Graphics::Renderable2d sprite2(Ruby::Maths::vec3(7, 1, 0), Ruby::Maths::vec2(2, 3), Ruby::Maths::vec4(0.2f, 0, 1, 1), shader);

	Ruby::Graphics::Simple2dRenderer renderer;

	while (!window.Closed())
	{
		window.Clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Ruby::Maths::vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));

		renderer.submit(&sprite1);
		renderer.submit(&sprite2);

		renderer.flush();

		window.Update();
	}
}