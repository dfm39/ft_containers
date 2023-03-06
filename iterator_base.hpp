#ifndef ITERATOR_BASE_H
# define ITERATOR_BASE_H

# include <memory>
# include <cstddef>

namespace ft
{
	/* Iterator Base Class is used tp derive iterator classes from it */
	template <
		class Category,
		class T,
		class Pointer = T*,
		class Reference = T&,
		class Distance = ptrdiff_t>
	struct iterator
	{
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Distance	difference_type;
	};

	/* Iterator traits class is defining properties of iterators*/
	template <class Iter>
	struct iterator_traits
	{
		/* Iter is the iterator type to retrive properties for */
		typedef 		 Iter						iterator_type;
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::difference_type		difference_type;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		/* Specialization for pointer Type T* which makes it possible to useall iterator-based algorithms with raw pointers */
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::ptrdiff_t					difference_type;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		/* Specialization for pointer Type const T* */
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::ptrdiff_t					difference_type;
	};

	template <class Iter>
	class reverse_iterator
	{
		public:
		typedef Iter														iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		
		/* Default Constructor */
		reverse_iterator() : _iterator()
		{}

		/* Base iterator Constructor */
		explicit reverse_iterator(iterator_type src) : _iterator(src)
		{}

		/*Constructs reverse_iterator from a different type rev_iterator */
		template <typename It>
		reverse_iterator(reverse_iterator<It> const & src) : _iterator(src.base())
		{}

		/* Destructor */
		virtual ~reverse_iterator()
		{}

		/* Get base */
		iterator_type	base() const
		{
			return this->_iterator;
		}

		/* Copy Assignment Overload*/
		reverse_iterator &	operator=(reverse_iterator const & rhs)
		{
			this->_iterator = rhs.base();
			return *this;
		}

		reference	operator*() const
		{
			iterator_type	it(this->_iterator);
			return *(--it);
		}

		pointer operator->() const
		{
			return &(this->operator*());
		}

		reference operator[](difference_type n) const
		{
			return (this->base()[-n -1]);
		}

		/* In- & Decrement Operators */
		reverse_iterator &	operator++()
		{
			this->_iterator--;
			return *this;
		}
		reverse_iterator	operator++(int)
		{
			reverse_iterator it = *this;
			this->_iterator--;
			return it;
		}
		reverse_iterator &	operator--()
		{
			this->_iterator++;
			return *this;
		}
		reverse_iterator	operator--(int)
		{
			reverse_iterator it = *this;
			this->_iterator++;
			return it;
		}

		/* Arithmetic operators */
		reverse_iterator	operator+(difference_type const & n) const
		{
			return reverse_iterator(this->_iterator.operator-(n));
		}
		reverse_iterator	operator-(difference_type const & n) const
		{
			return reverse_iterator(this->_iterator.operator+(n));
		}

		/* Addition & Subtraction assignment operators */
		reverse_iterator &	operator+=(difference_type const & n)
		{
			this->_iterator -= n;
			return *this;
		}
		reverse_iterator &	operator-=(difference_type const & n)
		{
			this->_iterator += n;
			return *this;
		}
		
		private:
		iterator_type	_iterator;
	};

		/* Inequality & Equality operators */
		template <typename It_l, typename It_r>
		bool operator==(reverse_iterator<It_l> & lhs, reverse_iterator<It_r> & rhs)
		{
			return lhs.base() == rhs.base();
		}
		template <typename It_l, typename It_r>
		bool operator!=(reverse_iterator<It_l> & lhs, reverse_iterator<It_r> & rhs)
		{
			return lhs.base() != rhs.base();
		}
		
		/* Bigger / equal, smaller / equal overloads  */
		template <typename It_l, typename It_r>
		bool operator<(reverse_iterator<It_l> & lhs, reverse_iterator<It_r> & rhs)
		{
			return lhs.base() > rhs.base();
		}
		template <typename It_l, typename It_r>
		bool operator>(reverse_iterator<It_l> & lhs, reverse_iterator<It_r> & rhs)
		{
			return lhs.base() < rhs.base();
		}
		template <typename It_l, typename It_r>
		bool operator<=(reverse_iterator<It_l> & lhs, reverse_iterator<It_r> & rhs)
		{
			return lhs.base() >= rhs.base();
		}
		template <typename It_l, typename It_r>
		bool operator>=(reverse_iterator<It_l> & lhs, reverse_iterator<It_r> & rhs)
		{
			return lhs.base() <= rhs.base();
		}

	template <typename It>
	reverse_iterator<It>	operator+(typename reverse_iterator<It>::difference_type const & n, reverse_iterator<It> & rhs)
	{
		return reverse_iterator<It>(rhs.base().operator-(n));
	}
	template <typename It_l, typename It_r>
	typename reverse_iterator<It_l>::difference_type	operator-(reverse_iterator<It_l> const & lhs, reverse_iterator<It_r> const & rhs)
	{
		return rhs.base().base() - lhs.base().base();
	}
}
#endif
