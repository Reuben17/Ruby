#pragma once

#ifdef RUBY_EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

#include "graphics/label.h"
#include "graphics/sprite.h"
#include "graphics/renderer2d.h"
#include "graphics/batchrenderer2d.h"
#include "graphics/window.h"
#include "graphics/layers/layer.h"

#include "maths/maths.h"
#include "utils/timer.h"

#ifdef RUBY_EMSCRIPTEN

static void dispatch_main(void* fp)
{
	std::function<void()>* func = (std::function<void()>*)fp;
	(*func)();
}

#endif

namespace Ruby {

	class Rubyy
	{
	private:
		Graphics::Window* m_Window;
		Timer* m_Timer;
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;
	protected:
		Rubyy()
			: m_FramesPerSecond(0), m_UpdatesPerSecond(0)
		{

		}

		virtual ~Rubyy()
		{
			delete m_Timer;
			delete m_Window;
		}

		Graphics::Window* createWindow(const char* name, int width, int height)
		{
			m_Window = new Graphics::Window(name, width, height);
			return m_Window;
		}

	public:
		void start()
		{
			init();
			run();
		}

	protected:
		// Runs once upon initialization
		virtual void init() = 0;
		// Runs once per second
		virtual void tick() { }
		// Runs 60 times per second
		virtual void update() { }
		// Runs as fast as possible (unless vsync is enabled)
		virtual void render() = 0;

		const unsigned int getFPS() const { return m_FramesPerSecond; }
		const unsigned int getUPS() const { return m_UpdatesPerSecond; }
	private:
		void run()
		{
			m_Timer = new Timer();
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;

#ifdef RUBY_EMSCRIPTEN
			std::function<void()> mainLoop = [&]() {
#else
			while (!m_Window->Closed())
			{
#endif
				m_Window->Clear();
				if (m_Timer->elapsed() - updateTimer > updateTick)
				{
					update();
					updates++;
					updateTimer += updateTick;
				}
				render();
				frames++;
				m_Window->Update();
				if (m_Timer->elapsed() - timer > 1.0f)
				{
					timer += 1.0f;
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					frames = 0;
					updates = 0;
					tick();
				}
#ifdef RUBY_EMSCRIPTEN
			};
			emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
#else
				}
#endif
		}
	};

}