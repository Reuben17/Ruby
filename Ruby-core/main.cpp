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
#include "src/graphics/FontManager.h"

#define TEST_50K_SPRITES 0
#define TEST_PRETTY 1

#if 0
	int main()
	{
		Ruby::Graphics::Window window("Ruby!", 960, 540);

		Ruby::Maths::mat4 ortho = Ruby::Maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

		Ruby::Graphics::Shader* shader = new Ruby::Graphics::Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
		shader->enable();
		shader->setUniform2f("light_pos", Ruby::Maths::vec2(4.0f, 1.5f));

		Ruby::Graphics::Tilelayer layer(shader);


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

		for (float y = -9.0f; y < 9.0f; y++)
		{
			for (float x = -16.0f; x < 16.0f; x++)
			{
				int r = rand() % 256;
				int g = rand() % 256;
				int b = rand() % 256;

				int col = 0xffffff << 24 | b << 16 | g << 8 | r;

				layer.add(new Ruby::Graphics::Sprite(x, y, 0.9f, 0.9f, col));
				//if (rand() % 4 == 0)
					//layer.add(new Ruby::Graphics::Sprite(x, y, 0.9f, 0.9f, col));
				//else
					//layer.add(new Ruby::Graphics::Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
			}
		}
#endif

		Ruby::Graphics::Group* g = new Ruby::Graphics::Group(Ruby::Maths::mat4::translation(Ruby::Maths::vec3(-15.8f, 6.5f, 0.0f)));
		Ruby::Graphics::Label* fps = new Ruby::Graphics::Label("", 0.4f, 0.4f, 0xff00ffff);
		g->add(new Ruby::Graphics::Sprite(0, 0, 6, 2.0f, 0x000505DD));
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
			shader->setUniform2f("light_pos", Ruby::Maths::vec2((float)(x * 32.0f / window.GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.GetHeight())));

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
#else
#include "ext/gorilla-audio/ga.h"
#include "ext/gorilla-audio/gau.h"
#include <stdio.h>

static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
{
	gc_int32* flag = (gc_int32*)(in_context);
	*flag = 1;
	ga_handle_destroy(in_handle);
}

int main()
{
	gau_Manager* mgr;
	ga_Mixer* mixer;
	ga_Sound* sound;
	ga_Handle* handle;
	gau_SampleSourceLoop* loopSrc = 0;
	gau_SampleSourceLoop** pLoopSrc = &loopSrc;
	gc_int32 loop = 0;
	gc_int32 quit = 0;

	/* Initialize library + manager */
	gc_initialize(0);
	mgr = gau_manager_create();
	mixer = gau_manager_mixer(mgr);

	/* Create and play shared sound */
	if (!loop)
		pLoopSrc = 0;
	sound = gau_load_sound_file("Evacuate.wav", "wav");
	handle = gau_create_handle_sound(mixer, sound, &setFlagAndDestroyOnFinish, &quit, pLoopSrc);
	ga_handle_play(handle);

	/* Bounded mix/queue/dispatch loop */
	while (!quit)
	{
		gau_manager_update(mgr);
		printf("%d / %d\n", ga_handle_tell(handle, GA_TELL_PARAM_CURRENT), ga_handle_tell(handle, GA_TELL_PARAM_TOTAL));
		gc_thread_sleep(1);
	}

	/* Clean up sound */
	ga_sound_release(sound);

	/* Clean up library + manager */
	gau_manager_destroy(mgr);
	gc_shutdown();
}
#endif