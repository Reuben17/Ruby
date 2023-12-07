#include "tilelayer.h"

namespace Ruby { namespace Graphics {
	Tilelayer::Tilelayer(Shader* shader)
		:Layer(new BatchRenderer2d(),shader,Maths::mat4::orthographic(-16.0f,16.0f,-9.0f,9.0f,-1.0f,1.0f))
	{
	}

	Tilelayer::~Tilelayer()
	{
	}

}}
