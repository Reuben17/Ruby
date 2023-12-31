#pragma once

#define GAU_THREAD_POLICY_MULTI 2

#include <vector>
#include "sound.h"

#include "../../ext/gorilla-audio/ga.h"
#include "../../ext/gorilla-audio/gau.h"

namespace Ruby{
	namespace Audio {

		class SoundManager
		{
		private:
			friend class Sound;

			static gau_Manager* m_Manager;
			static ga_Mixer* m_Mixer;

			static std::vector<Sound*> m_Sounds;
		public:
			static void init();
			static void add(Sound* sound);
			static Sound* get(const std::string& name);
			static void update();
			static void clear();
		private:
			SoundManager() { }
		};
}
}