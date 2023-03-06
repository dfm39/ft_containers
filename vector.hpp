#ifndef VECTOR_H
# define VECTOR_H

# include <memory>
# include <stdexcept>
# include <utility>
# include <algorithm>
# include <cstring>


# include <stdio.h>
# include <string.h>
# include <iostream>
# include "ra_iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template < 
		typename T, 
		typename Allocator = std::allocator<T> >
	class vector
	{
		public:
		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename ft::ra_iterator<value_type>			iterator;
		typedef typename ft::const_ra_iterator<value_type>		const_iterator;
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		/*___________________________*/
		/*---- MEMBER FUNCITONS -----*/
		/*---------------------------*/

		/* Default Constructor */
		explicit vector (const allocator_type & alloc = allocator_type()) 
			: _capacity(0) , _begin(NULL) , _end(NULL) , _allocator(alloc)
		{}
		/*Creates an instance of allocator type and sets private values to 0/NULL*/

		/* Fill Constructor */
		explicit vector (size_type n, const value_type & value = value_type(), const allocator_type & alloc = allocator_type()) 
			: _capacity(n) , _begin(NULL) , _end(NULL) , _allocator(alloc)
		{
			if (0 < this->_capacity)
			{
				this->_begin = this->_allocate(n);
				this->_end = this->_begin;
				for (size_type i = 0; i < n; i++)
					this->_allocator.construct(this->_end++, value);
			}
		}
		
		pointer	_allocate(size_type const n)
		{
			if (this->max_size() < n)
				throw std::length_error("size_type \'new_capacity\' exceeds maximum capacity");
			return	this->_allocator.allocate(n);
		}
		/*Constructs an instance of the value_type (T<?>) and an instance of std::allocator sets capaity to n*/
			
		/* Range Constructor */
		template <class InputIt>
		vector(InputIt first, InputIt last, const allocator_type & alloc = allocator_type(), typename enable_if<!is_integral<InputIt>::value>::type* = 0)
			: _capacity(0) , _begin(NULL) , _end(NULL) , _allocator(alloc)
		{
			this->assign(first, last);
		}

		/* Copy Constructor */
		vector (const vector& src) 
			: _capacity(src._capacity)
		{
			this->_begin = this->_allocator.allocate(this->_capacity);
			this->_end = this->_begin;
			for (size_type i = 0; i < src.size(); i++)
				this->_allocator.construct(this->_end++, *(src.data() + i));
		}

		/* Destructor */
		~vector()
		{
			this->clear();
			if (this->_begin != NULL)
				this->_allocator.deallocate(this->_begin, this->_capacity);
		}

		/* Copy Overload */
		vector &	operator=(vector const & rhs)
		{
			this->~vector();
			new (this) vector(rhs);
			return *this;
		}

		void	assign(size_type count, value_type const & value)
		{
			if (this->_capacity < count)
			{
				this->~vector();
				new (this) vector(count, value);
			}
			else
			{
				this->clear();
				for (size_type i = 0; i < count; i++)
		 			this->_allocator.construct(this->_end++, value);
			}
		}

		template <class InputIt>
		void	assign(InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value>::type* = 0)
		{
			typedef typename iterator_traits<InputIt>::iterator_category	it_type;
			_assign_type(first, last, it_type());
		}

		allocator_type	get_allocator() const
		{
			return this->_allocator;
		}
		/*______________________*/
		/*--- ELEMENT ACCESS ---*/
		/*----------------------*/
		
		/* At Function */
		reference	at(size_type pos)
		{
			if (this->size() <= pos)
				throw std::out_of_range("out of bounds");
			return *(this->_begin + pos);
		}
		const_reference	at(size_type pos) const
		{
			if (this->size() <= pos)
				throw std::out_of_range("out of bounds");
			return *(this->_begin + pos);
		}

		reference	operator[](difference_type pos)
		{
			return *(this->_begin + pos);
		}

		const_reference	operator[](difference_type pos) const
		{
			return *(this->_begin + pos);
		}

		/* Front & back functions */
		reference	front()
		{
			return *this->_begin;
		}
		const_reference	front() const
		{
			return *this->_begin;
		}
		reference	back()
		{
			return *(this->_end - 1);
		}
		const_reference	back() const
		{
			return *(this->_end - 1);
		}

		/* Data function*/
		value_type *	data()
		{
			return this->_begin;
		}
		const value_type *	data() const
		{
			return this->_begin;
		}
		/*_________________*/
		/*--- ITERATORS ---*/

		iterator	begin()
		{
			iterator it(this->_begin);
			return (it);
		}

		iterator	end()
		{
			iterator it(this->_end);
			return (it);
		}

		const_iterator	begin() const
		{
			const_iterator it(this->_begin);
			return (it);
		}

		const_iterator	end() const
		{
			const_iterator it(this->_end);
			return (it);
		}

		reverse_iterator	rbegin()
		{
			reverse_iterator it(this->_end);
			return (it);
		}

		reverse_iterator	rend()
		{
			reverse_iterator it(this->_begin);
			return (it);
		}

		const_reverse_iterator	rbegin() const
		{
			const_reverse_iterator it(this->_end);
			return (it);
		}

		const_reverse_iterator	rend() const
		{
			const_reverse_iterator it(this->_begin);
			return (it);
		}
		/*________________*/
		/*--- CAPACITY ---*/
		/*----------------*/

		bool empty() const
		{
			return this->size() == 0;
		}
		
		size_type	size() const
		{
			return this->_end - this->_begin;
		}

		size_type max_size() const
		{
			return this->_allocator.max_size();
		}

		void	reserve(size_type new_capacity)
		{
			if (this->max_size() < new_capacity)
				throw std::length_error("size_type \'new_capacity\' exceeds maximum capacity");
			if (this->_capacity < new_capacity)
				_reallocate(new_capacity);
		}

		size_type	capacity() const
		{
			return this->_capacity;
		}
		/*_________________*/
		/*--- MODIFIERS ---*/
		/*-----------------*/

		void	clear()
		{
			while (this->_begin != this->_end)
			{
				this->_allocator.destroy(--this->_end);
			}
		}

		iterator	insert(const_iterator pos, const T& value)
		{
			size_type distance = pos.base() - this->_begin;
			this->insert(pos, 1, value);
			return this->_begin + distance;
		}

		iterator	insert(const_iterator pos, size_type count, const T& value)
		{
			size_type distance = pos.base() - this->_begin;
			vector tmp(count, value);
			this->insert(pos, tmp.begin(), tmp.end());
			return this->_begin + distance;
		}

		template <class InputIt>
		iterator	insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value>::type* = 0)
		{
			typedef typename iterator_traits<InputIt>::iterator_category	it_type;
			size_type	distance = this->_end - pos.base();
			_insert_type(pos, first, last, it_type());
			return this->_begin + distance;
		}


		iterator	erase(iterator pos)
		{
			if (pos.base() == this->_end)
				return pos;
			size_type position = pos.base() - this->_begin;
			size_type new_size = this->size() - 1;
			size_type diff = new_size - position;
			if (ft::is_integral<value_type>::value)
				std::memmove(pos.base(), pos.base() + 1, diff * sizeof(value_type));
			else
			{
				for (size_type i = position; i < new_size; ++i)
					this->_begin[i] = this->_begin[i + 1];
			}
			this->_allocator.destroy(--this->_end);
			return pos;
		}

		iterator	erase(iterator first, iterator last)
		{
			if (first == last) 
				return first;
			size_type position = first.base() - this->_begin;
			size_type r_len = last - first;
			size_type new_size = this->size() - r_len;
			size_type diff = new_size - position;
			if (!r_len)
			{
				this->clear();
				return first;
			}
			if (ft::is_integral<value_type>::value)
				std::memmove(first.base(), first.base() + r_len, diff * sizeof(value_type));
			else
			{
				for (size_type i = position; i < new_size; ++i)
					this->_begin[i] = this->_begin[i + r_len];
			}
			resize(new_size);
			return first;
		}

		void	push_back(value_type const & value)
		{
			if (this->size() < this->_capacity)
			{
				this->_allocator.construct(this->_end++, value);
			}
			else
			{
				this->_reallocate(this->_capacity == 0 ? 1 : this->_capacity * 2);
				this->_allocator.construct(this->_end++, value);
			}
		}

		void	pop_back()
		{
			this->_allocator.destroy(--this->_end);
		}

		void	resize(size_type count, T value = T())
		{
			size_type size = this->size();
			if (this->_capacity < count)
			{
				if (this->max_size() < count)
					throw std::length_error("size_type \'count\' exceeds maximum capacity");
				if (this->_capacity * 2  < count)
					this->_reallocate(count);
				else
					this->_reallocate(this->_capacity * 2);
			}
			if (size < count)
			{
				while (size < count)
				{
					this->_allocator.construct(this->_end, value);
					count--; this->_end++;
				}
			}
			while (count < size)
			{
				this->_allocator.destroy(this->_end - 1);
				this->_end--; size--;
			}
		}
		
		void	swap(vector & other)
		{
			size_type		capacity_tmp	= this->_capacity;
			pointer			begin_tmp		= this->_begin;
			pointer			end_tmp			= this->_end;
			allocator_type	allocator_tmp	= this->_allocator;

			this->_capacity		= other._capacity;
			this->_begin		= other._begin;
			this->_end 			= other._end;
			this->_allocator	= other._allocator;

			other._capacity		= capacity_tmp;
			other._begin		= begin_tmp;
			other._end			= end_tmp;
			other._allocator	= allocator_tmp;
		}

		private:
		size_type		_capacity;
		pointer			_begin;
		pointer			_end;
		allocator_type	_allocator;

		void	_reallocate(size_type new_n)
		{
			pointer realloc = this->_allocator.allocate(new_n);
			size_type	size = this->size();
			for (size_type i = 0; i < size; i++)
			{
				this->_allocator.construct(realloc + i, this->_begin[i]);
				this->_allocator.destroy(_begin + i);
			}
			if (this->_begin != NULL)
				this->_allocator.deallocate(this->_begin, this->_capacity);
			this->_end = realloc + size;
			this->_begin = realloc;
			if (new_n == 0)
				return;
			this->_capacity = new_n;
		}

		template <class InputIt>
		void _assign_type(InputIt first, InputIt last, std::forward_iterator_tag)
		{
			size_type n = 0;
			for (InputIt It = first; It != last; It++)
				n++;
			this->clear();
			if (this->_capacity < n)
			{
				if (this->_begin != NULL)
					this->_allocator.deallocate(this->_begin, this->_capacity);
				this->_capacity = n;
				this->_begin = this->_allocator.allocate(n);
				this->_end = this->_begin;
			}
			for (size_type i = 0; i < n; i++)
				this->_allocator.construct(this->_end++, *first++);
		}

		template <class InputIt>
		void _assign_type(InputIt first, InputIt last, std::input_iterator_tag)
		{
			this->clear();
			vector tmp;
			for (; first != last; first++)
				tmp.push_back(*first);
			this->assign(tmp.begin(), tmp.end());
		}

		template <class InputIt>
		void	_insert_type(const_iterator pos, InputIt first, InputIt last, std::forward_iterator_tag)
		{
			size_type	r_len = 0;
			size_type	new_capacity = 0;
			size_type	distance = this->_end - pos.base();
			pointer		new_begin;
			pointer		new_end;
			pointer		helper;

			for (InputIt It = first; It != last; It++)
				r_len++;
			if (this->_capacity < this->size() + r_len)
			{
				if (this->_capacity * 2 <this->size() + r_len)
					new_capacity = this->size() + r_len;
				else
					new_capacity = this->_capacity * 2;
				new_begin = this->_allocator.allocate(new_capacity);
				new_end = new_begin;
				helper = this->_begin;
				try
				{
					while (helper != pos.base())
						this->_allocator.construct(new_end++, *helper++);
					while (first != last)
						this->_allocator.construct(new_end++, *first++);
					while (helper != this->_end)
						this->_allocator.construct(new_end++, *helper++);
				}
				catch (...)
				{
					while (new_end != new_begin)
						this->_allocator.destroy(--new_end);
					this->_allocator.deallocate(new_begin, new_capacity);
					throw;
				}
				this->~vector();
				this->_begin = new_begin;
				this->_end = new_end;
				this->_capacity = new_capacity;
			}
			else
			{
				helper = this->_begin + (this->size() - distance);
				for (pointer back = this->_end + r_len - 1; this->_end + r_len - distance - 1 < back; back--)
				{
					this->_allocator.destroy(back - r_len);
					this->_allocator.construct(back, back[-r_len]);
				}
				for (size_type i = 0; i < r_len; i++)
					this->_allocator.construct(helper++, *(first++));
				this->_end += r_len;
			}
		}

		template <class InputIt>
		void	_insert_type(const_iterator pos, InputIt first, InputIt last, std::input_iterator_tag)
		{
			vector tmp;
			for (; first != last; first++)
				tmp.push_back(*first);
			this->insert(pos, tmp.begin(), tmp.end());
		}
	};

	/*__________________________*/
	/*-- RELATIONAL OPERATORS --*/
	/*--------------------------*/

	template <class T, class Alloc>
	bool	operator==(ft::vector<T, Alloc> const & lhs, ft::vector<T, Alloc> const & rhs)
	{
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}
	template <class T, class Alloc>
	bool	operator!=(ft::vector<T, Alloc> const & lhs, ft::vector<T, Alloc> const & rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
	bool	operator<(ft::vector<T, Alloc> const & lhs, ft::vector<T, Alloc> const & rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool	operator>(ft::vector<T, Alloc> const & lhs, ft::vector<T, Alloc> const & rhs)
	{
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
	template <class T, class Alloc>
	bool	operator<=(ft::vector<T, Alloc> const & lhs, ft::vector<T, Alloc> const & rhs)
	{
		return !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
		template <class T, class Alloc>
	bool	operator>=(ft::vector<T, Alloc> const & lhs, ft::vector<T, Alloc> const & rhs)
	{
		return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	/*	FT::SWAP FUNCTION: UNCOMMENT FOR TERMINATOR TEST & CRASH_TEST, UNCOMMENTING	*/
	/*	THIS WILL CAUSE AMBIGUITY IN CONTAINERS TEST & CRASH_TEST. IF YOU			*/
	/*	UNCOMMENT THIS, COMMENT THE SWAP IMPLEMENTATION BELOW TO BYPASS AMBIGUITY	*/
	// template<class T, class Alloc>
	// void swap(ft::vector<T, Alloc> & a, ft::vector<T, Alloc> & b)
	// {
	// 	a.swap(b);
	// }
}

/* VECTOR SWAP IMPLEMENTATION IN STD::SWAP 								*/
/* (PUT AS COMMAND TO RUN CONTAINERS TEST AND CONTAINERS CRASH TEST)	*/
namespace std
{
	template<class T, class Alloc>
	void swap(ft::vector<T, Alloc> & a, ft::vector<T, Alloc> & b)
	{
		a.swap(b);
	}
}

#endif