#pragma once

#include "../Renderable2d.h"

namespace Ruby {
	namespace Graphics {

		class Group : public Renderable2d
		{
		private:
			std::vector<Renderable2d*> m_Renderables;
			Maths::mat4 m_TransformationMatrix;
		public:
			Group(const Maths::mat4& transform);
			void add(Renderable2d* renderable);
			void submit(Renderer2d* renderer) const override;
		};
} }