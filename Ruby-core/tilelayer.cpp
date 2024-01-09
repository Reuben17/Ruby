#include "tilelayer.h"

	Tilelayer::Tilelayer(Ruby::Graphics::Shader* shader)
		:Layer(new Ruby::Graphics::BatchRenderer2d(),shader,Ruby::Maths::mat4::orthographic(-16.0f,16.0f,-9.0f,9.0f,-1.0f,1.0f))
	{
	}

	Tilelayer::~Tilelayer()
	{
	}

