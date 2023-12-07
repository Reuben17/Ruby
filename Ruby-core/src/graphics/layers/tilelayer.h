#pragma once
#pragma once

#include "layer.h"
#include "../batchrenderer2d.h"

namespace Ruby {
	namespace Graphics {

		class Tilelayer: public Layer
		{
		public:
			Tilelayer(Shader* shader);
			~Tilelayer();
		};

	}
}