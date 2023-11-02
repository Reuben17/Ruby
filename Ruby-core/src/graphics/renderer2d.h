#pragma once

#include "GL/glew.h"
#include "../maths/maths.h"
#include "Renderable2d.h"

namespace Ruby { namespace Graphics {

	class Renderer2d
	{
	public:
		virtual void submit(const Renderable2d* renderable) = 0;
		virtual void flush() = 0;
	};

}}