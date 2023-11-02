#pragma once
#include "renderer2d.h"
#include <deque>

namespace Ruby { namespace Graphics {

	class Simple2dRenderer : public Renderer2d
	{
	private:
		std::deque<const Renderable2d*> m_RenderQueue;
	public:
		void submit(const Renderable2d* renderable) override;
		void flush() override;
	};
}}