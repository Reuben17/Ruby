#include "sound.h"
#include "SoundManager.h"

namespace Ruby {
	namespace Audio {

		void destroyOnFinish(ga_Handle* in_handle, void* in_context);
		void loopOnFinish(ga_Handle* in_handle, void* in_context);

		Sound::Sound(const std::string& name, const std::string& filename)
			:m_Name(name),m_Filename(filename), m_Playing(false)
		{
			std::vector<std::string> split = split_string(m_Filename, '.');
			if (split.size() < 2)
			{
				std::cout << "[Sound] Invalid file name '" << m_Filename << "'!" << std::endl;
				return;
			}
#ifdef RUBY_EMSCRIPTEN
#else
			m_Sound = gau_load_sound_file(filename.c_str(), split.back().c_str());

			if (m_Sound == nullptr)
				std::cout << "[Sound] Could not load file '" << m_Filename << "'!" << std::endl;	
#endif
		}
		Sound::~Sound()
		{
			/* Clean up sound */
#ifdef RUBY_EMSCRIPTEN
#else
			ga_sound_release(m_Sound);
#endif
		}
		void Sound::play()
		{
#ifdef RUBY_EMSCRIPTEN
#else
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &destroyOnFinish, &quit, NULL);
			m_Handle->sound = this;
			ga_handle_play(m_Handle);
#endif
			m_Playing = true;
		}
		void Sound::loop()
		{
#ifdef RUBY_EMSCRIPTEN
#else
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &loopOnFinish, &quit, NULL);
			m_Handle->sound = this;
			ga_handle_play(m_Handle);
#endif
			m_Playing = true;
		}
		void Sound::pause()
		{
			if (!m_Playing)
				return;

			m_Playing = false;
#ifdef RUBY_EMSCRIPTEN
#else
			ga_handle_stop(m_Handle);
#endif
		}
		void Sound::resume()
		{
			if (m_Playing)
				return;

			m_Playing = true;
#ifdef RUBY_EMSCRIPTEN
#else
			ga_handle_play(m_Handle);
#endif
		}
		void Sound::stop()
		{
			if (!m_Playing)
				return;

#ifdef RUBY_EMSCRIPTEN
#else
			ga_handle_stop(m_Handle);
#endif
			m_Playing = false;
		}

		void Sound::setGain(float gain)
		{
			if (!m_Playing)
			{
				std::cout << "[Sound] Cannot set gain! Sound is not currently playing!" << std::endl;
				return;
			}
			m_Gain = gain;
#ifdef RUBY_EMSCRIPTEN
#else
			ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, gain);
#endif
		}

#ifdef RUBY_EMSCRIPTEN
#else
		void destroyOnFinish(ga_Handle* in_handle, void* in_context)
		{
			Sound* sound = (Sound*)in_handle->sound;
			sound->stop();
		}


		void loopOnFinish(ga_Handle* in_handle, void* in_context)
		{
			Sound* sound = (Sound*)(in_handle->sound);
			sound->loop();
			ga_handle_destroy(in_handle);
		}
#endif
	}
}