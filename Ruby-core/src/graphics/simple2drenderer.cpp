#include "simple2drenderer.h"
#include "Renderable2d.h"

namespace Ruby {
	namespace Graphics {

		void Simple2dRenderer::submit(const Renderable2d* renderable)
		{
			m_RenderQueue.push_back((StaticSprite*)renderable);
		}

		void Simple2dRenderer::flush()
		{
			while (!m_RenderQueue.empty())
			{
				const StaticSprite* sprite = m_RenderQueue.front();
				sprite->getVAO()->bind();
				sprite->getIBO()->bind();

				sprite->getShader().setUniformMat4("ml_matrix", Maths::mat4::translation(sprite->getPosition())); 
				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				sprite->getIBO()->unbind();
				sprite->getVAO()->unbind();

				m_RenderQueue.pop_front();
			}
		}
	}
}
