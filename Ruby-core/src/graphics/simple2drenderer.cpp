#include "simple2drenderer.h"

namespace Ruby { namespace Graphics {

	void Simple2dRenderer::submit(const Renderable2d* renderable)
	{
		m_RenderQueue.push_back(renderable);
	}
	void Simple2dRenderer::flush()
	{
		while (!m_RenderQueue.empty())
		{
			const Renderable2d* renderable = m_RenderQueue.front();
			renderable->getVAO()->bind();
			renderable->getIBO()->bind();

			renderable->getShader().setUniformMat4("ml_matrix", Maths::mat4::translation(renderable->getPosition()));
			glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

			renderable->getVAO()->unbind();
			renderable->getIBO()->unbind();

			m_RenderQueue.pop_front();
		}
	}
}}
