#pragma once

#include "../Renderable2d.h"
#include "../renderer2d.h"

namespace Ruby {
	namespace Graphics{

		class Layer
		{
		protected:
			Renderer2d* m_Renderer;
			std::vector<Renderable2d*> m_Renderables;
			Shader* m_Shader;
			Maths::mat4 m_ProjectionMatrix;
		protected:
		public:
			Layer(Renderer2d* renderer, Shader* shader, Maths::mat4 projectionMatrix);
			virtual ~Layer();
			virtual void add(Renderable2d* renderable);
			virtual void render();

			inline const std::vector<Renderable2d*>& getRenderables() const { return m_Renderables; }
		};

}}