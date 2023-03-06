#ifndef	RBT_ITERATOR_H
# define RBT_ITERATOR_H

# include "rbt.hpp" 
# include "iterator_base.hpp"

namespace ft
{
	template <class Tnode, class Ttree>
	class const_rbt_iterator;

	template <typename Tnode, typename Ttree>
	class rbt_iterator : public iterator<std::bidirectional_iterator_tag, typename Ttree::value_type>
	{
		public:
		typedef typename Ttree::value_type																value_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::pointer				pointer;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::reference			reference;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
		typedef Tnode																					node_type;
		typedef Tnode *																					node_pointer;

		rbt_iterator() : _ptr(NULL)
		{}

		/* Constructor takes Pointer */
		rbt_iterator(node_pointer src) : _ptr(src)
		{}

		/* Copy Constructor*/
		rbt_iterator(const rbt_iterator &	src) : _ptr(src._ptr)
		{}

		template<typename Utree>
		rbt_iterator(const rbt_iterator<Tnode, Utree> &	src) : _ptr(src.base())
		{}

		/* Destructor */
		virtual ~rbt_iterator()
		{}

		node_pointer	base() const
		{
			return this->_ptr;
		}

		/* Copy Assignment Overload*/
		rbt_iterator &	operator=(const rbt_iterator & rhs)
		{
			this->_ptr = rhs.base();
			return *this;
		}

		/* Dereference operator */
		reference	operator*() const
		{
			return this->_ptr->content;
		}

		/* Access arrow operator */
		pointer	operator->() const
		{
			return &(this->_ptr->content);
		}

		/* In- & Decrement Operators */
		rbt_iterator &	operator++()
		{
			this->_successor();
			return *this;
		}
		rbt_iterator	operator++(int)
		{
			rbt_iterator it = *this;
			this->_successor();
			return it;
		}
		rbt_iterator &	operator--()
		{
			this->_predecessor();
			return *this;
		}
		rbt_iterator	operator--(int)
		{
			rbt_iterator it = *this;
			this->_predecessor();
			return it;
		}

		bool operator==(const rbt_iterator<Tnode, Ttree> & rhs)
		{
			return this->_ptr == rhs.base();
		}

		bool operator==(const const_rbt_iterator<Tnode, Ttree> & rhs) const
		{
			return this->_ptr == rhs.base();
		}

		bool operator!=(const rbt_iterator<Tnode, Ttree> & rhs)
		{
			return this->_ptr != rhs.base();
		}

		bool operator!=(const const_rbt_iterator<Tnode, Ttree> & rhs) const
		{
			return this->_ptr != rhs.base();
		}

		node_pointer _ptr;
		protected:

		void	_successor()
		{
			node_pointer helper;
			if (!this->_ptr->right->null_node)
			{
				helper = this->_ptr->right;
				while (!helper->left->null_node)
					helper = helper->left;
			}
			else if (this->_ptr->right->null_node && this->_ptr->right->parent == this->_ptr)
				helper = this->_ptr->right;
			else
			{
				helper = this->_ptr->parent;
				while (!helper->null_node && this->_ptr == helper->right)
				{
					this->_ptr = helper;
					helper = this->_ptr->parent;
				}
			}
			this->_ptr = helper;
		}

		void	_predecessor()
		{
			node_pointer helper;
			if (this->_ptr->null_node)
			{
				helper = this->_ptr->parent;
			}
			else if (!this->_ptr->left->null_node)
			{
				helper = this->_ptr->left;
				while (!helper->right->null_node)
					helper = helper->right;
			}
			else
			{
				helper = this->_ptr->parent;
				while (!helper->null_node && this->_ptr == helper->left)
				{
					this->_ptr = helper;
					helper = this->_ptr->parent;
				}
			}
			this->_ptr = helper;
		}
	};
	
	template <typename Tnode, typename Ttree>
	class const_rbt_iterator : public iterator<std::bidirectional_iterator_tag, const typename Ttree::value_type>
	{
		public:
		typedef const typename Ttree::value_type																value_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::pointer				pointer;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::reference			reference;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
		typedef Tnode																					node_type;
		typedef Tnode *																					node_pointer;

		/* Default Constructor */
		const_rbt_iterator() : _ptr(NULL)
		{}

		/* Constructor takes Pointer */
		const_rbt_iterator(node_pointer	src) : _ptr(src)
		{}

		/* Copy Constructor*/
		const_rbt_iterator(const const_rbt_iterator &	src) : _ptr(src._ptr)
		{}

		const_rbt_iterator(const rbt_iterator<Tnode, Ttree> &rhs) : _ptr(rhs.base())
		{}

		template<typename Utree>
		const_rbt_iterator(const rbt_iterator<Tnode, Utree> &	src) : _ptr(src.base())
		{}

		template<typename Utree>
		const_rbt_iterator(const const_rbt_iterator<Tnode, Utree> &	src) : _ptr(src.base())
		{}

		/* Destructor */
		virtual ~const_rbt_iterator()
		{}

		node_pointer	base() const
		{
			return this->_ptr;
		}

		/* Copy Assignment Overload*/
		const_rbt_iterator &	operator=(const_rbt_iterator const & rhs)
		{
			this->_ptr = rhs.base();
			return *this;
		}
		
		const_rbt_iterator &	operator=(rbt_iterator<Tnode, Ttree> const & rhs)
		{
			this->_ptr = rhs.base();
			return *this;
		}

		/* Dereference operator */
		reference	operator*() const
		{
			return this->_ptr->content;
		}

		/* Access arrow operator */
		pointer	operator->() const
		{
			return &(this->_ptr->content);
		}

		/* In- & Decrement Operators */
		const_rbt_iterator &	operator++()
		{
			this->_successor();
			return *this;
		}
		const_rbt_iterator	operator++(int)
		{
			const_rbt_iterator it = *this;
			this->_successor();
			return it;
		}
		const_rbt_iterator &	operator--()
		{
			this->_predecessor();
			return *this;
		}
		const_rbt_iterator	operator--(int)
		{
			const_rbt_iterator it = *this;
			this->_predecessor();
			return it;
		}

		bool operator==(const const_rbt_iterator & rhs) const
		{
			return this->base() == rhs.base();
		}

		bool operator==(const rbt_iterator<Tnode, Ttree> & rhs)
		{
			return this->base() == rhs.base();
		}

		bool operator!=(const const_rbt_iterator & rhs) const
		{
			return this->base() != rhs.base();
		}

		bool operator!=(const rbt_iterator<Tnode, Ttree> & rhs)
		{
			return this->base() != rhs.base();
		}

		private:
		node_pointer _ptr;

		void	_successor()
		{
			node_pointer helper;
			if (!this->_ptr->right->null_node)
			{
				helper = this->_ptr->right;
				while (!helper->left->null_node)
					helper = helper->left;
			}
			else if (this->_ptr->right->null_node && this->_ptr->right->parent == this->_ptr)
				helper = this->_ptr->right;
			else
			{
				helper = this->_ptr->parent;
				while (!helper->null_node && this->_ptr == helper->right)
				{
					this->_ptr = helper;
					helper = this->_ptr->parent;
				}
			}
			this->_ptr = helper;
		}

		void	_predecessor()
		{
			node_pointer helper;
			if (this->_ptr->null_node)
			{
				helper = this->_ptr->parent;
			}
			else if (!this->_ptr->left->null_node)
			{
				helper = this->_ptr->left;
				while (!helper->right->null_node)
					helper = helper->right;
			}
			else
			{
				helper = this->_ptr->parent;
				while (!helper->null_node && this->_ptr == helper->left)
				{
					this->_ptr = helper;
					helper = this->_ptr->parent;
				}
			}
			this->_ptr = helper;
		}
	};
}

#endif