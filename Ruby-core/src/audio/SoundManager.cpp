#include "SoundManager.h"

namespace Ruby {
	namespace Audio
	{
		gau_Manager* SoundManager::m_Manager = nullptr;
		ga_Mixer* SoundManager::m_Mixer = nullptr;
		std::vector<Sound*> SoundManager::m_Sounds;

		void SoundManager::init()
		{
			gc_initialize(0);
			m_Manager = gau_manager_create();
			m_Mixer = gau_manager_mixer(m_Manager);
		}

		void SoundManager::add(Sound* sound)
		{
			m_Sounds.push_back(sound);
		}

		Sound* SoundManager::get(const std::string& name)
		{
			for (Sound* sound : m_Sounds)
			{
				if (sound->getName() == name)
				{
					return sound;
				}
			}
			return nullptr;
		}

		void SoundManager::update()
		{
			//while (!quit)
			//{
				gau_manager_update(SoundManager::m_Manager);
				//printf("%d / %d\n", ga_handle_tell(m_Handle, GA_TELL_PARAM_CURRENT), ga_handle_tell(m_Handle, GA_TELL_PARAM_TOTAL));
			//	gc_thread_sleep(1);
			//}
		}

		void SoundManager::clear()
		{
			for (int i = 0; i < m_Sounds.size(); i++)
			{
				delete m_Sounds[i];
				
			}
			/* Clean up library + manager */
			gau_manager_destroy(m_Manager);
			gc_shutdown();
		}

	}
}