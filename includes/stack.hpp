#ifndef STACK_H
# define STACK_H

#include "vector.hpp"

namespace ft
{
	template <
		class T,
		class Container = ft::vector<T> >
	class stack
	{
		public:

		typedef 			Container					container_type;
		typedef typename	Container::value_type		value_type;
		typedef typename	Container::size_type		size_type;
		typedef typename	Container::reference		reference;
		typedef typename	Container::const_reference	const_reference;

		explicit stack(const Container & cont = Container()) : _c(cont)
		{}

		~stack()
		{}

		stack &	operator=(stack const & src)
		{
			this->_c = src._c;
			return *this;
		}
		/*______________________*/
		/*--- ELEMENT ACCESS ---*/

		reference	top()
		{
			return this->_c.back();
		}

		const_reference	top() const
		{
			return this->_c.back();
		}
		/*________________*/
		/*--- CAPACITY ---*/

		bool	empty() const
		{
			return this->_c.empty();
		}

		size_type	size() const
		{
			return this->_c.size();
		}
		/*_________________*/
		/*--- MODIFIERS ---*/
		
		void	push(const value_type & value)
		{
			this->_c.push_back(value);
		}

		void	pop()
		{
			this->_c.pop_back();
		}

		template<typename A, typename B>
		friend bool operator== (const stack<A,B>& lhs, const stack<A,B>& rhs);
		
		template<typename A, typename B>
		friend bool operator<  (const stack<A,B>& lhs, const stack<A,B>& rhs);

		protected:
		container_type _c;
	};

	template<class T, class Container>
	bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._c == rhs._c;
	}

	template<class T, class Container>
	bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template<class T, class Container>
	bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._c < rhs._c;
	}

	template<class T, class Container>
	bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs < rhs || lhs == rhs;
	}

	template<class T, class Container>
	bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return !(lhs <= rhs);
	}

	template<class T, class Container>
	bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return !(lhs < rhs);
	}

}
#endif
