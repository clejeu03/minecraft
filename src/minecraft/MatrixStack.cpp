#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <minecraft/MatrixStack.hpp>

namespace minecraft {
	MatrixStack::MatrixStack() {
		m_stack.push(glm::mat4(1.));
	}

	void MatrixStack::Push() {
		m_stack.push(m_stack.top());
	}

	void MatrixStack::Pop() {
		m_stack.pop();
	}

	void MatrixStack::Mult(const glm::mat4& m) {
		m_stack.top() *= m;
	}

	const glm::mat4 MatrixStack::Top() const {
		return m_stack.top();
	}
	
	void MatrixStack::Set(const glm::mat4& m) {
		Pop();
		m_stack.push(m);
	}

	void MatrixStack::Scale(const glm::vec3& v) {
		m_stack.top() = glm::scale(m_stack.top(),v);
	}

	void MatrixStack::Translate(const glm::vec3& v) {
		m_stack.top() = glm::translate(m_stack.top(),v);
	}

	void MatrixStack::Rotate(float deg, const glm::vec3& v) {
		m_stack.top() = glm::rotate(m_stack.top(),deg,v);
	}
}
