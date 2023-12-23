#include "src/graphics/Window.h"
#include "src/maths/maths.h"
#include "src/utils/timer.h"

#include "src/graphics/Shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/Renderable2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/static_sprite.h"
#include "src/graphics/batchrenderer2d.h"
#include "src/graphics/sprite.h"
#include <time.h>
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"
#include <FreeImage.h>
#include "src/graphics/texture.h"
#include "src/graphics/label.h"

#define TEST_50K_SPRITES 0
#define TEST_PRETTY 1


int main()
{
	Ruby::Graphics::Window window("Ruby!", 960, 540);

	Ruby::Maths::mat4 ortho = Ruby::Maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Ruby::Graphics::Shader* shader = new Ruby::Graphics::Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader->enable();
	shader->setUniform2f("light_pos", Ruby::Maths::vec2(4.0f, 1.5f));

	Ruby::Graphics::Tilelayer layer(shader);

#if 1
#if TEST_50K_SPRITES
	for (float y = -9.0f; y < 9.0f; y += 0.1)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1)
		{
			layer.add(new Ruby::Graphics::Sprite(x, y, 0.09f, 0.09f, Ruby::Maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)));
		}
	}
#elif TEST_PRETTY

	Ruby::Graphics::Texture* textures[] =
	{
		new Ruby::Graphics::Texture("test.png"),
		new Ruby::Graphics::Texture("test.jpg"),
		new Ruby::Graphics::Texture("fortnite.jpg"),
	};

	for (float y = -9.0f; y < 9.0f; y ++)
	{
		for (float x = -16.0f; x < 16.0f; x ++)
		{
			layer.add(new Ruby::Graphics::Sprite(x, y, 0.9f, 0.9f, Ruby::Maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)));
			//if (rand() % 4 == 0)
				//layer.add(new Ruby::Graphics::Sprite(x, y, 0.9f, 0.9f, Ruby::Maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)));
			//else
				//layer.add(new Ruby::Graphics::Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}
#endif
	
	Ruby::Graphics::Group* g = new Ruby::Graphics::Group(Ruby::Maths::mat4::translation(Ruby::Maths::vec3(-15.8f, 6.5f, 0.0f)));
	Ruby::Graphics::Label* fps = new Ruby::Graphics::Label("", 0.4f, 0.4f, Ruby::Maths::vec4(1, 1, 0, 1));
	g->add(new Ruby::Graphics::Sprite(0, 0, 6, 2.0f, Ruby::Maths::vec4(0.3f, 0.3f, 0.3f, 0.0f)));
	g->add(fps);

	layer.add(g);



	GLint texIDs[] =
	{
		0,1,2,3,4,5,6,7,8,9
	};

	shader->enable();
	shader->setUniform1iv("textures", texIDs, 10);

	Ruby::Timer time;
	float timer = 0;
	unsigned int frames = 0;
	
	while (!window.Closed())
	{
		window.Clear();
		double x, y;
		window.getMousePosition(x, y);
		shader->enable();
		shader->setUniform2f("light_pos", Ruby::Maths::vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
		

		layer.render();
	
		
		window.Update();
		frames++;
		//printf("Sprites: %d\n", sprites.size());
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			fps->text = std::to_string(frames) + "fps";
			printf("%d fps\n", frames);
			frames = 0;
		}
	}
	for (int i = 0; i < 3; i++)
		delete textures[i];

}
#endif

#if 0
int main()
{
	const char* filename = "test.png";

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP* dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	std::cout << width << "," << height << std::endl;

		

	return 0;
}
#endif