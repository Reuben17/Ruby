#pragma once

#include <vector>
#include "GL/glew.h"
#include "../maths/maths.h"

namespace Ruby { namespace Graphics {

	class Renderable2d;
	class Renderer2d
	{
	protected:
		std::vector<Maths::mat4> m_TransformationStack;
		const Maths::mat4* m_TransformationBack;
	protected:
		Renderer2d()
		{
			m_TransformationStack.push_back(Maths::mat4::identity());
			m_TransformationBack = &m_TransformationStack.back();
		}
	public:
		void push(const Maths::mat4& matrix,bool override = false)
		{
			if (override)
				m_TransformationStack.push_back(matrix);
			else
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

			m_TransformationBack = &m_TransformationStack.back();
		}
		void pop()
		{
			if (m_TransformationStack.size() > 1)
				m_TransformationStack.pop_back();

			m_TransformationBack = &m_TransformationStack.back();
		}

		virtual void begin() {}
		virtual void submit(const Renderable2d* renderable) = 0;
		virtual void end() {}
		virtual void flush() = 0;
	};

}}