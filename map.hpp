#ifndef MAP_H
# define MAP_H

# include "rbt_iterator.hpp"
# include "rbt.hpp"
# include "utils.hpp"
# include "iterator_base.hpp"

namespace ft
{

	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
		typedef				Key													key_type;
		typedef				T													mapped_type;
		typedef				ft::pair<const key_type, mapped_type>				value_type;
		typedef				std::size_t											size_type;
		typedef				std::ptrdiff_t										difference_type;
		typedef				Compare												key_compare;
		typedef				Allocator											allocator_type;
		typedef 			value_type &										reference;
		typedef 			const value_type &									const_reference;
		typedef typename	allocator_type::pointer								pointer;
		typedef typename	allocator_type::const_pointer						const_pointer;
		
		class value_compare;
		typedef				ft::rbt<value_type, value_compare, allocator_type>	tree_type;

		typedef typename	ft::rbt_iterator<typename tree_type::node_type, tree_type>			iterator;
		typedef typename	ft::const_rbt_iterator<typename tree_type::node_type, tree_type>	const_iterator;
		typedef typename	ft::reverse_iterator<iterator>										reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>								const_reverse_iterator;

		/*____________________*/
		/*--- MEMBER CLASS ---*/
		/*--------------------*/

		class value_compare 
			: public std::binary_function<value_type, value_type, bool>
		{
			public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			value_compare() : comp(key_compare())
			{}

			value_compare(key_compare c) : comp(c)
			{}

			bool operator()(const value_type& lhs, const value_type& rhs) const 
			{
				return comp(lhs.first, rhs.first);
			}

			protected:
				key_compare comp;
		};

		/*_______________________*/
		/*---MEMBER FUNCITONS ---*/
		/*-----------------------*/

		explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
			: _tree(comp, alloc), _comp(comp)
		{}

		template< class InputIt >
		map(InputIt first, InputIt last, const key_compare & comp = key_compare(), const Allocator& alloc = allocator_type())
			: _tree(comp, alloc), _comp(comp)
		{
			this->insert(first, last);
		}

		map(const map& src) : _tree(src._tree), _comp(src._comp)
		{}

		~map()
		{}

		map &	operator=(const map & rhs)
		{
			this->_tree = rhs._tree;
			this->_comp = rhs._comp;
			return *this;
		}

		allocator_type get_allocator() const
		{
			return this->_tree.get_allocator();
		}

		/*______________________*/
		/*--- ELEMENT ACCESS ---*/
		/*----------------------*/

		mapped_type& at (Key const & key)
		{
		iterator	it = find(key);
		if (it == this->end())
			throw std::out_of_range ("out of bounds");
		return it->second;
		}

		const mapped_type& at(Key const & key) const
		{
			const_iterator	it = find(key);
			if (it == this->end())
				throw std::out_of_range ("out of bounds");
			return it->second;
		}

		mapped_type& operator[](const Key& key)
		{
			iterator	it = find(key);
			if (it == this->end())
					it = insert(value_type(key, mapped_type())).first;
			return it->second;
		}

		/*_________________*/
		/*--- ITERATORS ---*/
		/*-----------------*/

		iterator	begin()
		{
			return iterator(this->_tree.begin());
		}

		const_iterator	begin() const
		{
			return const_iterator(this->_tree.begin());
		}

		iterator	end()
		{
			return iterator(this->_tree.end());
		}

		const_iterator	end() const
		{
			return const_iterator(this->_tree.end());
		}

		reverse_iterator	rbegin()
		{
			return reverse_iterator(this->_tree.end());
		}

		const_reverse_iterator	rbegin() const
		{
			return const_reverse_iterator(this->_tree.end());
		}

		reverse_iterator	rend()
		{
			return reverse_iterator (this->_tree.begin());
		}

		const_reverse_iterator	rend() const
		{
			return const_reverse_iterator (this->_tree.begin());
		}
		/*________________*/
		/*--- CAPACITY ---*/
		/*----------------*/

		bool	empty() const
		{
			return this->_tree.empty();
		}

		size_type	size() const
		{
			return this->_tree.size();
		}

		size_type	max_size() const
		{
			return this->_tree.max_size();
		}

		/*_________________*/
		/*--- MODIFIERS ---*/
		/*-----------------*/

		void	clear()
		{
			this->_tree.clear();
		}

		ft::pair<iterator, bool> insert(const value_type &	value)
		{
			ft::pair<typename tree_type::node_pointer, bool>	helper = this->_tree.insert_node(value);
			return ft::pair<iterator, bool>(iterator(helper.first), helper.second);
		}

		iterator insert(iterator pos, const value_type &	val)
		{
			(void) pos;
			return iterator(this->_tree.insert_node(val).first);
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last)
		{
			while (first != last)
				this->_tree.insert_node(*(first++));
		}

		void	erase(iterator	pos)
		{
			this->_tree.erase(*pos);
		}

		size_type erase (key_type const &	key)
		{
			return this->_tree.erase(value_type(key, mapped_type()));
		}

		void	erase(iterator first, iterator last)
		{
			while (first != last)
				this->_tree.erase(*(first++));
		}

		void	swap(map & other)
		{
			this->_tree.swap(other._tree);
		}

		/*______________*/
		/*--- LOOKUP ---*/
		/*--------------*/

		size_type count(const Key& key) const
		{
			if (this->find(key) == this->end())
				return 0;
			else
				return 1;
		}

		iterator find(const Key& key)
		{
			return iterator(this->_tree.find_node(value_type(key, mapped_type())));
		}

		const_iterator find(const Key& key) const
		{
			return const_iterator(this->_tree.find_node(value_type(key, mapped_type())));
		}

		ft::pair<iterator,iterator> equal_range(const Key& key)
		{
			return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
		{
			return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
		}

		iterator lower_bound(const Key& key)
		{
			iterator it(this->_tree.lower_bound(value_type(key, mapped_type())));
			return (it);
		}

		const_iterator lower_bound(const Key& key) const
		{
			const_iterator it(this->_tree.lower_bound(value_type(key, mapped_type())));
			return (it);
		}

		iterator upper_bound(const Key& key)
		{
			iterator it(this->_tree.upper_bound(value_type(key, mapped_type())));
			return (it);
		}

		const_iterator upper_bound(const Key& key) const
		{
			const_iterator it(this->_tree.upper_bound(value_type(key, mapped_type())));
			return (it);
		}

		/*_________________*/
		/*--- OBSERVERS ---*/
		/*-----------------*/

		key_compare key_comp() const
		{
			return this->_comp;
		}

		value_compare value_comp() const
		{
			return value_compare(this->_comp);
		}

		private:
		tree_type	_tree;
		key_compare _comp;

		// void	_print()
		// {
		// 	this->_tree.print_p();
		// }
	};
	

	template <class Key, class T, class Compare, class Allocator>
	bool	operator==(ft::map<Key, T, Compare, Allocator> const & lhs, ft::map<Key, T, Compare, Allocator> const & rhs)
	{
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}
	template <class Key, class T, class Compare, class Allocator>
	bool	operator!=(ft::map<Key, T, Compare, Allocator> const & lhs, ft::map<Key, T, Compare, Allocator> const & rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class Key, class T, class Compare, class Allocator>
	bool	operator<(ft::map<Key, T, Compare, Allocator> const & lhs, ft::map<Key, T, Compare, Allocator> const & rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class Key, class T, class Compare, class Allocator>
	bool	operator>(ft::map<Key, T, Compare, Allocator> const & lhs, ft::map<Key, T, Compare, Allocator> const & rhs)
	{
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
	template <class Key, class T, class Compare, class Allocator>
	bool	operator<=(ft::map<Key, T, Compare, Allocator> const & lhs, ft::map<Key, T, Compare, Allocator> const & rhs)
	{
		return !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
		template <class Key, class T, class Compare, class Allocator>
	bool	operator>=(ft::map<Key, T, Compare, Allocator> const & lhs, ft::map<Key, T, Compare, Allocator> const & rhs)
	{
		return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	/*	FT::SWAP FUNCTION: UNCOMMENT FOR TERMINATOR TEST & CRASH_TEST, UNCOMMENTING	*/
	/*	THIS WILL CAUSE AMBIGUITY IN CONTAINERS TEST & CRASH_TEST. IF YOU			*/
	/*	UNCOMMENT THIS, COMMENT THE SWAP IMPLEMENTATION BELOW TO BYPASS AMBIGUITY	*/
	template <class Key, class T, class Compare, class Allocator>
	void swap(ft::map<Key, T, Compare, Allocator> & a, ft::map<Key, T, Compare, Allocator> & b)
	{
		a.swap(b);
	}
}

/* VECTOR SWAP IMPLEMENTATION IN STD::SWAP 								*/
/* (PUT AS COMMAND TO RUN CONTAINERS TEST AND CONTAINERS CRASH TEST)	*/
// namespace std
// {
// 	template <class Key, class T, class Compare, class Allocator>
// 	void swap(ft::map<Key, T, Compare, Allocator> & a, ft::map<Key, T, Compare, Allocator> & b)
// 	{
// 		a.swap(b);
// 	}
// }

#endif