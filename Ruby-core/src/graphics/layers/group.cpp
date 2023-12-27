#include "group.h"

namespace Ruby {namespace Graphics {
		Group::Group(const Maths::mat4& transform)
			:m_TransformationMatrix(transform)
		{
		}
		Group::~Group()
		{
			for (int i = 0; i < m_Renderables.size(); i++)
			{
				delete m_Renderables[i];
			}
		}
		void Group::add(Renderable2d* renderable)
		{
			m_Renderables.push_back(renderable);
		}
		void Group::submit(Renderer2d* renderer) const
		{
			renderer->push(m_TransformationMatrix);

			for (const Renderable2d* renderable : m_Renderables)
				renderable->submit(renderer);

			renderer->pop();
		}
	}
}
