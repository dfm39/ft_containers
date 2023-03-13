#ifndef RA_ITERATOR_H
# define RA_ITERATOR_H

# include "iterator_base.hpp"

namespace ft
{
	template <typename T>
	class const_ra_iterator;

	template <typename T>
	class ra_iterator : public iterator<std::random_access_iterator_tag, T>
	{
		public:
		typedef typename iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename iterator<std::random_access_iterator_tag, T>::value_type			value_type;
		typedef typename iterator<std::random_access_iterator_tag, T>::pointer				pointer;
		typedef typename iterator<std::random_access_iterator_tag, T>::reference			reference;
		typedef typename iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;

		/* Default Constructor */
		ra_iterator() : _ptr(NULL)
		{}

		/* Constructor takes Pointer */
		ra_iterator(pointer src) : _ptr(src)
		{}

		/* Copy Constructor*/
		ra_iterator(ra_iterator const &src) : _ptr(src.base())
		{}
		
		/* Destructor */
		virtual ~ra_iterator()
		{}

		/* Get base */
		pointer	base() const
		{
			return this->_ptr;
		}

		/* Copy Assignment Overload*/
		ra_iterator &	operator=(ra_iterator const & rhs)
		{
			this->_ptr = rhs.base();
			return *this;
		}

		/* Dereference operator */
		reference	operator*() const
		{
			return *this->_ptr;
		}

		/* Access arrow operator */
		pointer	operator->() const
		{
			return this->_ptr;
		}

		/* Offset dereference operator */
		reference	operator[](difference_type n) const
		{
			return *(this->_ptr + n);
		}

		/* In- & Decrement Operators */
		ra_iterator &	operator++()
		{
			this->_ptr++;
			return *this;
		}
		ra_iterator	operator++(int)
		{
			ra_iterator it = *this;
			this->_ptr++;
			return it;
		}
		ra_iterator &	operator--()
		{
			this->_ptr--;
			return *this;
		}
		ra_iterator	operator--(int)
		{
			ra_iterator it = *this;
			this->_ptr--;
			return it;
		}

		/* Arithmetic operators */
		ra_iterator	operator+(difference_type const & n) const
		{
			return this->_ptr + n;
		}
		ra_iterator	operator-(difference_type const & n) const
		{
			return this->_ptr - n;
		}

		/* Addition & Subtraction assignment operators */
		ra_iterator &	operator+=(difference_type const & n)
		{
			this->_ptr += n;
			return *this;
		}
		ra_iterator &	operator-=(difference_type const & n)
		{
			this->_ptr -= n;
			return *this;
		}

		/* Inequality & Equality operators */
		template <typename U>
		bool operator==(const ra_iterator<U> & rhs) const
		{
			return this->_ptr == rhs.base();
		}
		template <typename U>
		bool operator==(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr == rhs.base();
		}
		template <typename U>
		bool operator!=(const ra_iterator<U> & rhs) const
		{
			return this->_ptr != rhs.base();
		}
		template <typename U>
		bool operator!=(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr != rhs.base();
		}

		/* Bigger / equal, smaller / equal overloads  */
		template <typename U>
		bool operator<(const ra_iterator<U> & rhs) const
		{
			return this->_ptr < rhs.base();
		}
		template <typename U>
		bool operator<(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr < rhs.base();
		}
		template <typename U>
		bool operator>(const ra_iterator<U> & rhs) const
		{
			return this->_ptr > rhs.base();
		}
		template <typename U>
		bool operator>(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr > rhs.base();
		}
		template <typename U>
		bool operator<=(const ra_iterator<U> & rhs) const
		{
			return this->_ptr <= rhs.base();
		}
		template <typename U>
		bool operator<=(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr <= rhs.base();
		}
		template <typename U>
		bool operator>=(const ra_iterator<U> & rhs) const
		{
			return this->_ptr >= rhs.base();
		}
		template <typename U>
		bool operator>=(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr >= rhs.base();
		}

		private:
		pointer _ptr;
	};

	template <typename T>
	class const_ra_iterator : public iterator<std::random_access_iterator_tag, T>
	{
		public:
		typedef typename iterator<std::random_access_iterator_tag, const T>::iterator_category	iterator_category;
		typedef typename iterator<std::random_access_iterator_tag, const T>::value_type		value_type;
		typedef typename iterator<std::random_access_iterator_tag, const T>::pointer			pointer;
		typedef typename iterator<std::random_access_iterator_tag, const T>::reference			reference;
		typedef typename iterator<std::random_access_iterator_tag, const T>::difference_type	difference_type;

		/* Default Constructor */
		const_ra_iterator() : _ptr(NULL)
		{}

		/* Constructor takes Pointer */
		const_ra_iterator(pointer ptr) : _ptr(ptr)
		{}

		/* Copy Constructors*/
		const_ra_iterator(const_ra_iterator const &src) : _ptr(src.base())
		{}
		template <typename U>
		const_ra_iterator(ra_iterator<U> const &src) : _ptr(src.base())
		{}

		/* Destructor */
		virtual ~const_ra_iterator()
		{}

		/* Pointer Getter */
		pointer	base() const
		{
			return this->_ptr;
		}

		const_ra_iterator &	operator=(const_ra_iterator const & rhs)
		{
			this->_ptr = rhs.base();
			return *this;
		}

				/* Offset dereference operator */
		reference	operator[](difference_type n) const
		{
			return *(this->_ptr + n);
		}

		/* Access arrow operator */
		pointer	operator->() const
		{
			return this->_ptr;
		}

		/* Dereference operator */
		reference	operator*() const
		{
			return *this->_ptr;
		}

		/* In- & Decrement Operators } */
		const_ra_iterator &	operator++()
		{
			this->_ptr++;
			return *this;
		}
		const_ra_iterator	operator++(int)
		{
			const_ra_iterator it = *this;
			this->_ptr++;
			return it;
		}
		const_ra_iterator &	operator--()
		{
			this->_ptr--;
			return *this;
		}
		const_ra_iterator	operator--(int)
		{
			const_ra_iterator it = *this;
			this->_ptr--;
			return it;
		}

		/* Arithmetic operators */
		const_ra_iterator	operator+(difference_type const & n) const
		{
			return this->_ptr + n;
		}
		const_ra_iterator	operator-(difference_type const & n) const
		{
			return this->_ptr - n;
		}

		/* Addition & Subtraction assignment operators */
		const_ra_iterator &	operator+=(difference_type const & n)
		{
			this->_ptr += n;
			return *this;
		}
		const_ra_iterator &	operator-=(difference_type const & n)
		{
			this->_ptr -= n;
			return *this;
		}

		/* Inequality & Equality operators */
		template <typename U>
		bool operator==(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr == rhs.base();
		}
		template <typename U>
		bool operator==(const ra_iterator<U> & rhs) const
		{
			return this->_ptr == rhs.base();
		}
		template <typename U>
		bool operator!=(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr != rhs.base();
		}
		template <typename U>
		bool operator!=(const ra_iterator<U> & rhs) const
		{
			return this->_ptr != rhs.base();
		}

		/* Bigger / equal, smaller / equal overloads  */
		template <typename U>
		bool operator<(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr < rhs.base();
		}
		template <typename U>
		bool operator<(const ra_iterator<U> & rhs) const
		{
			return this->_ptr < rhs.base();
		}
		template <typename U>
		bool operator>(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr > rhs.base();
		}
		template <typename U>
		bool operator>(const ra_iterator<U> & rhs) const
		{
			return this->_ptr > rhs.base();
		}
		template <typename U>
		bool operator<=(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr <= rhs.base();
		}
		template <typename U>
		bool operator<=(const ra_iterator<U> & rhs) const
		{
			return this->_ptr <= rhs.base();
		}
		template <typename U>
		bool operator>=(const const_ra_iterator<U> & rhs) const
		{
			return this->_ptr >= rhs.base();
		}
		template <typename U>
		bool operator>=(const ra_iterator<U> & rhs) const
		{
			return this->_ptr >= rhs.base();
		}

		private:
		pointer _ptr;
	};

	/* Difference_type on lhs addition overload */
	template <typename U>
	ra_iterator<U>	operator+(typename ra_iterator<U>::difference_type const & n, ra_iterator<U> & rhs)
	{
		return rhs.base() + n;
	}
	template <typename U>
	const_ra_iterator<U>	operator+(typename const_ra_iterator<U>::difference_type const & n, const_ra_iterator<U> & rhs)
	{
		return rhs.base() + n;
	}
	template <typename U>
	typename ra_iterator<U>::difference_type	operator-(ra_iterator<U> const & lhs, ra_iterator<U> const & rhs)
	{
		return lhs.base() - rhs.base();
	}
	template <typename U>
	typename ra_iterator<U>::difference_type	operator-(const_ra_iterator<U> const & lhs, const_ra_iterator<U> const & rhs)
	{
		return lhs.base() - rhs.base();
	}
	template <typename U>
	typename ra_iterator<U>::difference_type	operator-(ra_iterator<U> const & lhs, const_ra_iterator<U> const & rhs)
	{
		return lhs.base() - rhs.base();
	}
	template <typename U>
	typename ra_iterator<U>::difference_type	operator-(const_ra_iterator<U> const & lhs, ra_iterator<U> const & rhs)
	{
		return lhs.base() - rhs.base();
	}
}

#endif
