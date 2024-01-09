#pragma once
#include "font.h"
#include <vector>

namespace Ruby {
	namespace Graphics
	{
		class FontManager
		{
		private:
			static std::vector<Font*> m_Fonts;
		public:
			static void add(Font* font);
			static Font* get();
			static Font* get(const std::string& name);
			static Font* get(const std::string& name,unsigned int size);
			static void clear();
		private:
			FontManager() { }
		};
	}
}