#include "FontManager.h"

namespace Ruby {
	namespace Graphics {

		std::vector<Font*> FontManager::m_Fonts;

		void FontManager::add(Font* font)
		{
			m_Fonts.push_back(font);
		}
		Font* FontManager::get(const std::string& name)
		{
			for (Font* font : m_Fonts)
			{
				if (font->getName() == name)
				{
					return font;
				}
			}
			return nullptr;
		}
		Font* FontManager::get(const std::string& name, unsigned int size)
		{
			for (Font* font : m_Fonts)
			{
				if (font->getSize() == size && font->getName() == name )
				{
					return font;
				}
			}
			return nullptr;
		}
		void FontManager::clear()
		{
			for (int i = 0; i < m_Fonts.size(); i++)
			{
				delete m_Fonts[i];
			}
		}
	}
}