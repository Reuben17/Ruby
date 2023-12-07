#include "layer.h"

namespace Ruby { namespace Graphics {
	Layer::Layer(Renderer2d* renderer, Shader* shader, Maths::mat4 projectionMatrix)
		:m_Renderer(renderer),m_Shader(shader),m_ProjectionMatrix(projectionMatrix)
	{
		m_Shader->enable();
		m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader->disable();
	}
	Layer::~Layer()
	{
		delete m_Renderer;
		delete m_Shader;
		
		for (int i = 0; i < m_Renderables.size(); i++)
		{
			delete m_Renderables[i];
		}
	}
	void Layer::add(Renderable2d* renderable)
	{
		m_Renderables.push_back(renderable);
	}
	void Layer::render()
	{
		m_Shader->enable();

		m_Renderer->begin();
		for (const Renderable2d* renderable : m_Renderables)
		{
			renderable->submit(m_Renderer);
		}
		
		m_Renderer->end();
		m_Renderer->flush();
		
	}
} }

