#ifndef MINECRAFT_MATRIXSTACK_HPP_
#define MINECRAFT_MATRIXSTACK_HPP_

#include <stack>
#include <glm/glm.hpp>

namespace minecraft {
	class MatrixStack {
		private:
			std::stack<glm::mat4> m_stack;
		public:
			MatrixStack();
			void Push();
			void Pop();
			void Mult(const glm::mat4&);
			const glm::mat4 Top() const;
			void Set(const glm::mat4&);
			void Scale(const glm::vec3&);
			void Translate(const glm::vec3&);
			void Rotate(float, const glm::vec3&);
	};
}

#endif
