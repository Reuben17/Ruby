#pragma once

#include "src/graphics/layers/layer.h"
#include "src/graphics/batchrenderer2d.h"


	class Tilelayer: public Ruby::Graphics::Layer
	{
	public:
		Tilelayer(Ruby::Graphics::Shader* shader);
		~Tilelayer();
	};

