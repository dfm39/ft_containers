#ifndef SET_H
# define SET_H

# include "rbt_iterator.hpp"
# include "rbt.hpp"
# include "utils.hpp"
# include "iterator_base.hpp"

namespace ft
{

	template<
		class Key,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<Key> >
	class set
	{
		public:
		typedef				Key													key_type;
		typedef				Key													value_type;
		typedef				std::size_t											size_type;
		typedef				std::ptrdiff_t										difference_type;
		typedef				Compare												key_compare;
		typedef				Compare												value_compare;
		typedef				Allocator											allocator_type;
		typedef 			value_type &										reference;
		typedef 			const value_type &									const_reference;
		typedef typename	allocator_type::pointer								pointer;
		typedef typename	allocator_type::const_pointer						const_pointer;
		
		typedef				ft::rbt<value_type, key_compare, allocator_type>	tree_type;

		typedef typename	ft::const_rbt_iterator<typename tree_type::node_type, tree_type>			iterator;
		typedef typename	ft::const_rbt_iterator<typename tree_type::node_type, tree_type>	const_iterator;
		typedef typename	ft::reverse_iterator<iterator>										reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>								const_reverse_iterator;


		/*_______________________*/
		/*---MEMBER FUNCITONS ---*/
		/*-----------------------*/

		explicit set(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
			: _tree(comp, alloc), _comp(comp)
		{}

		template< class InputIt >
		set(InputIt first, InputIt last, const key_compare & comp = key_compare(), const Allocator& alloc = allocator_type())
			: _tree(comp, alloc), _comp(comp)
		{
			this->insert(first, last);
		}

		set(const set& src) : _tree(src._tree), _comp(src._comp)
		{}

		~set()
		{}

		set &	operator=(const set & rhs)
		{
			this->_tree = rhs._tree;
			this->_comp = rhs._comp;
			return *this;
		}

		allocator_type get_allocator() const
		{
			return this->_tree.get_allocator();
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

		iterator insert(iterator	pos, const value_type &	val)
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

		size_type erase (const value_type &	value)
		{
			return this->_tree.erase(value);
		}

		void	erase(iterator first, iterator last)
		{
			while (first != last)
				this->_tree.erase(*(first++));
		}

		void	swap(set & other)
		{
			this->_tree.swap(other._tree);
		}

		/*______________*/
		/*--- LOOKUP ---*/
		/*--------------*/

		size_type count(const Key &	key) const
		{
			if (this->find(key) == this->end())
				return 0;
			else
				return 1;
		}

		iterator find(const value_type &	value)
		{
			return iterator(this->_tree.find_node(value));
		}

		const_iterator find(const value_type &	value) const
		{
			return const_iterator(this->_tree.find_node(value));
		}

		ft::pair<iterator, iterator> equal_range(const value_type &	value)
		{
			return ft::pair<iterator, iterator>(lower_bound(value), upper_bound(value));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const value_type &	value) const
		{
			return ft::pair<const_iterator, const_iterator>(lower_bound(value), upper_bound(value));
		}

		iterator lower_bound(const value_type &	value)
		{
			iterator it(this->_tree.lower_bound(value));
			return (it);
		}

		const_iterator lower_bound(const value_type &	value) const
		{
			const_iterator it(this->_tree.lower_bound(value));
			return (it);
		}

		iterator upper_bound(const value_type &	value)
		{
			iterator it(this->_tree.upper_bound(value));
			return (it);
		}

		const_iterator upper_bound(const value_type &	value) const
		{
			const_iterator it(this->_tree.upper_bound(value));
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
	};

	template <class Key, class Compare, class Allocator>
	bool	operator==(const ft::set<Key, Compare, Allocator> & lhs, const ft::set<Key, Compare, Allocator> & rhs)
	{
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}
	template <class Key, class Compare, class Allocator>
	bool	operator!=(const ft::set<Key, Compare, Allocator> & lhs, const ft::set<Key, Compare, Allocator> & rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class Key, class Compare, class Allocator>
	bool	operator<(const ft::set<Key, Compare, Allocator> & lhs, const ft::set<Key, Compare, Allocator> & rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class Key, class Compare, class Allocator>
	bool	operator>(const ft::set<Key, Compare, Allocator> & lhs, const ft::set<Key, Compare, Allocator> & rhs)
	{
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
	template <class Key, class Compare, class Allocator>
	bool	operator<=(const ft::set<Key, Compare, Allocator> & lhs, const ft::set<Key, Compare, Allocator> & rhs)
	{
		return !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
		template <class Key, class Compare, class Allocator>
	bool	operator>=(const ft::set<Key, Compare, Allocator> & lhs, const ft::set<Key, Compare, Allocator> & rhs)
	{
		return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	/*	FT::SWAP FUNCTION: UNCOMMENT FOR TERMINATOR TEST & CRASH_TEST, UNCOMMENTING	*/
	/*	THIS WILL CAUSE AMBIGUITY IN CONTAINERS TEST & CRASH_TEST. IF YOU			*/
	/*	UNCOMMENT THIS, COMMENT THE SWAP IMPLEMENTATION BELOW TO BYPASS AMBIGUITY	*/
	// template <class Key, class Compare, class Allocator>
	// void swap(ft::set<Key, Compare, Allocator> & a, ft::set<Key, Compare, Allocator> & b)
	// {
	// 	a.swap(b);
	// }
}

/* VECTOR SWAP IMPLEMENTATION IN STD::SWAP 								*/
/* (PUT AS COMMAND TO RUN CONTAINERS TEST AND CONTAINERS CRASH TEST)	*/
namespace std
{
	template <class Key, class Compare, class Allocator>
	void swap(ft::set<Key, Compare, Allocator> & a, ft::set<Key, Compare, Allocator> & b)
	{
		a.swap(b);
	}
}

#endif
