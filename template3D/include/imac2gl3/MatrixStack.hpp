#ifndef __MATRIXSTACK__
#define __MATRIXSTACK__

#include <stack>
#include <glm/glm.hpp>

class MatrixStack{ //ca marche pas donc bon... 
	private:
		std::stack<glm::mat4> m_Stack;
		
	public:
		MatrixStack(){
			m_Stack.push(glm::mat4(1.f));
		};
		inline void pop(){
			m_Stack.pop();
		};
		inline void push(){
			m_Stack.push(m_Stack.top());
		};
		inline const glm::mat4& top(){
			return m_Stack.top();
		};
		inline void mult(const glm::mat4& m){
			m_Stack.top()*=m;
		};
		void set(const glm::mat4& m){
			m_Stack.top()= m;
		};
		void scale(const glm::vec3& s){
			set(glm::scale(m_Stack.top(), s));
		};
		void translate(const glm::vec3& t){
			set(glm::translate(m_Stack.top(), t));
		};
		void rotate(float degrees, const glm::vec3& r){
			set(glm::rotate(m_Stack.top(), degrees, r));
		};
	
};


#endif
