#pragma once

#include <string>
#include "../maths/vec2.h"
#include "../../ext/freetype-gl/freetype-gl.h"

namespace Ruby {
	namespace Graphics {

		class Font
		{
		private:
			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;
			unsigned int m_Size;
		
			Ruby::Maths::vec2 m_Scale;
			std::string m_Name;
			std::string m_Filename;
		public:
			Font(std::string name,std::string filename,int size);

			void setScale(float x, float y);

			inline const unsigned int getID() const { return m_FTAtlas->id; }
			inline const Maths::vec2& getScale() const { return m_Scale; }
			inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }
			inline const std::string& getName() const { return m_Name; }
			inline const std::string& getFileName() const { return m_Filename; }
			inline const int getSize() const { return m_Size; }
		};
	}
}

