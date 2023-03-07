#ifndef RBT_H
# define RBT_H

# include <memory>
# include <string>
# include <iostream>
# include "utils.hpp"

# define BLACK true
# define RED false

namespace ft
{
	/*
	Red-Black Trees Properties:
	- Self-balancing tree
	- Every node is either red or black
	- the root is always black
	- every leaf, which is Nil is always black
	- if a node is red, then its children are black
	- every path from a node to any of its descendent nil node has the same amount of black nodes
	*/

	template <typename T>
	struct node
	{
		T		content;
		node	*parent;
		node	*left;
		node	*right;
		bool	colour;
		bool	null_node;

		node() 
			: content(T()), left(NULL), right(NULL), colour(BLACK), null_node(true)
		{
			this->parent = this;
		}
		node(const T & value) 
			: content(T(value)), parent(NULL), left(NULL), right(NULL), colour(RED), null_node(false)
		{}
	};

	template <class T,
		class Compare = std::less<T>,
		class Allocator = std::allocator<T> >
	class rbt
	{
		public:
		typedef				T														value_type;
		typedef				Compare													key_compare;
		typedef				std::size_t												size_type;
		typedef				std::ptrdiff_t											difference_type;
		typedef				node<T>													node_type;
		typedef				node<T> *												node_pointer;
		typedef	typename	Allocator::template rebind<node_type>::other			allocator_type;
		typedef 			value_type &											reference;
		typedef 			const value_type &										const_reference;
		typedef typename	allocator_type::pointer									pointer;
		typedef typename	allocator_type::const_pointer							const_pointer;

		/*_______________________*/
		/*---MEMBER FUNCITONS ---*/
		/*-----------------------*/

		rbt(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) 
			:  _nil(_create_nil_node()), _min(_nil), _max(_nil) , _root(_nil), _alloc(alloc), _compare(comp), _size(0)
		{}

		rbt(const rbt & src)
			: _nil(_create_nil_node()), _min(_nil), _max(_nil), _root(_nil), _alloc(), _compare(), _size()
		{
			*this = src;
		}

		~rbt()
		{
			this->clear();
			this->_clear_node(this->_nil);
		}

		rbt	&	operator=(const rbt & rhs)
		{
			this->clear();
			this->_alloc = rhs.get_allocator();
			this->_size = rhs.size();
			this->_compare = rhs.key_comp();
			if (0 < this->_size)
			{
				this->_root = this->_create_node(rhs.get_root()->content);
				this->_min = this->_root;
				this->_set_max(this->_root);
			}
			if (1 < this->_size)
			{
				this->_copy_nodes(this->_root, rhs.get_root());
			}
			this->_min = this->_minimum(this->_root);
			this->_set_max(this->_maximum(this->_root));
			return *this;
		}

		allocator_type get_allocator() const
		{
			return this->_alloc;
		}

		/*________________*/
		/*--- CAPACITY ---*/
		/*----------------*/

		bool	empty() const
		{
			return this->_size == 0;
		}

		size_type	size() const
		{
			return this->_size;
		}

		size_type	max_size() const
		{
			return this->_alloc.max_size();
		}

		/*_________________*/
		/*--- MODIFIERS ---*/
		/*-----------------*/

		void clear()
		{
			this->_clear_subtree(this->_root);
			this->_root = this->_nil;
			this->_min = this->_root;
			this->_set_max(this->_root);
			this->_size = 0;
		}

		ft::pair<node_pointer, bool>	insert_node(value_type const & value)
		{
			/* Insert First node as Root */
			bool	unique = true;
			if (this->_root->null_node)
			{
				this->_root = this->_create_node(value);
				this->_size++;
				this->_root->colour = BLACK;
				this->_min = this->_root;
				this->_set_max(this->_root);
				return ft::pair<node_pointer, bool>(this->_root, unique);
			}
			/* Find the postition of new_nodes parent.		*/
			/* Create the node, and set the node as			*/
			/* parents child, if content of node 			*/
			/* doesnt already exist							*/
			node_pointer	parent = this->_find_parent_node(value);
			node_pointer	new_node = this->_create_node(value);
			new_node->parent = parent;
			new_node = this->_set_child(parent, new_node);
			/* If value already exists in tree, postion		*/
			/* unique bool is set to false	*/
			if (this->_is_equal(parent->content, new_node->content))
				unique = false;
			else
			{
				/* If Parent is not black, tree needs to be		*/
				/* fixed with recoloring and rotation			*/
				this->_insert_extrema(new_node);
				if (parent->colour != BLACK)
					this->_fix_insertion(new_node);
			}
			return ft::pair<node_pointer, bool>(new_node, unique);
		}

		bool	erase(value_type const & value)
		{
			node_pointer	del_node = find_node(value);
			if (del_node->null_node)
				return false;
			this->_delete_node(del_node);
			return true;
		}

		void	swap(rbt &	other)
		{
			node_pointer		t_nil = this->_nil;
			node_pointer 		t_min = this->_min;
			node_pointer 		t_max = this->_max;
			node_pointer 		t_root = this->_root;
			allocator_type		t_alloc = this->_alloc;
			key_compare		t_compare = this->_compare;
			size_type			t_size = this->_size;

			this->_nil = other._nil;
			this->_min = other._min;
			this->_max = other._max;
			this->_root = other._root;
			this->_alloc = other._alloc;
			this->_compare = other._compare;
			this->_size = other._size;

			other._nil = t_nil;
			other._min = t_min;
			other._max = t_max;
			other._root = t_root;
			other._alloc = t_alloc;
			other._compare = t_compare;
			other._size = t_size;
		}

		/*______________*/
		/*--- LOOKUP ---*/
		/*--------------*/

		node_pointer	find_node(const value_type & value) const
		{
			node_pointer	helper = this->_root;
			while (!helper->null_node)
			{
				if (this->_is_smaller(value, helper->content))
					helper = helper->left;
				else if (this->_is_greater(value, helper->content))
					helper = helper->right;
				else
					break;
			}
			return helper;
		}

		node_pointer	lower_bound(value_type const & value) const
		{
			node_pointer helper = this->_root;
			node_pointer ret = this->_nil;

			while (!helper->null_node)
			{	
				if (!this->_is_smaller(helper->content, value))
				{
					ret = helper;
					helper = helper->left;
				}
				else
					helper = helper->right;
			}
			return ret;
		}

		node_pointer	upper_bound(value_type const & value) const
		{
			node_pointer helper = this->_root;
			node_pointer ret = this->_nil;

			while (!helper->null_node)
			{	
				if (this->_is_greater(helper->content, value))
				{
					ret = helper;
					helper = helper->left;
				}
				else
					helper = helper->right;
			}
			return ret;
		}

		/*_________________*/
		/*--- OBSERVERS ---*/
		/*-----------------*/

		key_compare	key_comp() const
		{
			return this->_compare;
		}

		/*_______________*/
		/*--- GETTERS ---*/
		/*---------------*/

		node_pointer	get_root() const
		{
			return this->_root;
		}

		node_pointer	begin() const
		{
			return this->_min;
		}

		node_pointer	end() const
		{
			return this->_nil;
		}


		private:
		node_pointer	_nil;
		node_pointer 	_min;
		node_pointer 	_max;
		node_pointer 	_root;
		allocator_type	_alloc;
		key_compare		_compare;
		size_type		_size;

		/*_______________________*/
		/*--- NODE PROPERTIES ---*/
		/*-----------------------*/

		bool	_is_left_child(node_pointer node) const
		{
			if (node->parent && (node->parent->left == node))
				return true;
			return false;
		}

		bool	_is_right_child(node_pointer node) const
		{
			if (node->parent && node->parent->right == node)
				return true;
			return false;
		}

		bool	_is_leafnode(node_pointer const &	node)
		{
			if (node->left == this->_nil && node->right == this->_nil)
				return true;
			return false;
		}

		bool	_has_one_child(node_pointer const &	node)
		{
			return (!node->left->null_node && node->right->null_node) || \
					(!node->right->null_node && node->left->null_node);
		}

		/*____________________________*/
		/*--- GET/SET RELATIONSHIP ---*/
		/*----------------------------*/

		node_pointer	_find_parent_node(const value_type & value)
		{
			node_pointer	helper = this->_root;
			while (!helper->null_node)
			{
				if (this->_is_smaller(value, helper->content) && !helper->left->null_node)
					helper = helper->left;
				else if (this->_is_greater(value, helper->content) && !helper->right->null_node)
					helper = helper->right;
				else
					break;
			}
			return helper;
		}

		/* If node already exists, parent is returned to pass the exisitng entry */
		node_pointer	_set_child(node_pointer const & parent, node_pointer const & new_node)
		{
			if (this->_is_smaller(new_node->content, parent->content))
				parent->left = new_node;
			else if (this->_is_greater(new_node->content, parent->content))
				parent->right = new_node;
			else
			{
				this->_clear_node(new_node);
				return parent;
			}
			this->_size++;
			return new_node;
		}

		node_pointer	_get_sibling(node_pointer const & node)
		{
			if (node->parent && node == node->parent->left)
				return node->parent->right;
			else if (node->parent && node == node->parent->right)
				return node->parent->left;
			else
				return NULL;
		}

		node_pointer	_get_single_child(node_pointer const &	node) const
		{
			if (!node->left->null_node)
				return node->left;
			else
				return node->right;
		}

		node_pointer	_predecessor(node_pointer	node) // Finds the node with the next smallest value
		{
			node_pointer helper = NULL;
			if (!node->left->null_node)
			{
				helper = node->left;
				while (!helper->right->null_node)
					helper = helper->right;
			}
			else if (node->parent)
			{
				helper = node->parent;
				while (!helper->null_node && node == helper->left)
				{
					node = helper;
					helper = node->parent;
				}
			}
			return helper;
		}

		/*__________________*/
		/*--- COMPARISON ---*/
		/*------------------*/

		bool	_is_smaller(value_type const & value1, value_type const & value2) const
		{
			return this->_compare(value1, value2);
		}

		bool	_is_greater(value_type const & value1, value_type const & value2) const
		{
			return this->_compare(value2, value1);
		}

		bool	_is_equal(value_type const & value1, value_type const & value2)
		{
			return !this->_compare(value1, value2) && !this->_compare(value2, value1);
		}

		/*_____________________*/
		/*--- NODE CREATION ---*/
		/*---------------------*/

		node_pointer	_create_nil_node()
		{
			node_pointer	new_node = this->_alloc.allocate(1);
			this->_alloc.construct(new_node, node_type());
			return new_node;
		}

		node_pointer	_create_node(value_type const & value)
		{
			node_pointer	new_node = this->_alloc.allocate(1);
			this->_alloc.construct(new_node, node_type(value));
			new_node->left = this->_nil;
			new_node->right = this->_nil;
			return new_node;
		}

		void	_copy_nodes(node_pointer dest, node_pointer src)
		{
			if (!src->left->null_node)
			{
				dest->left = this->_create_node(src->left->content);
				dest->left->parent = dest;
				dest->left->colour = src->left->colour;
				this->_copy_nodes(dest->left, src->left);
			}
			if (!src->right->null_node)
			{
				dest->right = this->_create_node(src->right->content);
				dest->right->parent = dest;
				dest->right->colour = src->right->colour;
				this->_copy_nodes(dest->right, src->right);
			}
		}
		
		/*_________________*/
		/*--- ROTATIONS ---*/
		/*-----------------*/

		void	_left_rotate(node_pointer node)
		{
			node_pointer	helper = node->right;
			node->right = helper->left;
			if (!helper->left->null_node)
				helper->left->parent = node;
			helper->parent = node->parent;
			if (this->_is_left_child(node))
				node->parent->left = helper;
			else if (this->_is_right_child(node))
				node->parent->right = helper;
			else
				this->_root = helper;
			helper->left = node;
			node->parent = helper;

		}

		void	_right_rotate(node_pointer node)
		{
			node_pointer	helper = node->left;
			node->left = helper->right;
			if (!helper->right->null_node)
				helper->right->parent = node;
			helper->parent = node->parent;
			if (this->_is_left_child(node))
				node->parent->left = helper;
			else if (this->_is_right_child(node))
				node->parent->right = helper;
			else
				this->_root = helper;
			helper->right = node;
			node->parent = helper;
		}

		/*_______________________________*/
		/*--- INSERT HELPER FUNCTIONS ---*/
		/*-------------------------------*/

		void	_fix_insertion(node_pointer node)
		{
			/* Loops until parent is black					*/
			while (node->parent && node->parent->colour == RED)
			{
				node_pointer	uncle = this->_get_sibling(node->parent);
				/* if uncle is red, recoloring is necessary */
				if (uncle->colour == RED)
				{
					if (node->parent->parent != this->_root)
						this->_recolour(node->parent->parent);
					this->_recolour(node->parent);
					this->_recolour(uncle);
					node = node->parent->parent;
				}
				else
				{
					if (this->_is_left_child(node->parent))
					{
						/* left-right rotation is necessary if	*/
						/* node is right child 					*/
						if (this->_is_right_child(node))
						{
							node = node->parent;
							_left_rotate(node);
						}
						this->_right_rotate(node->parent->parent);
						this->_recolour(node->parent);
						this->_recolour(node->parent->right);
					}
					else if (this->_is_right_child(node->parent))
					{
						/* right-left rotation is necessary if	*/
						/* node is right child 					*/
						if (this->_is_left_child(node))			//right-left rotation is necessary
						{
							node = node->parent;
							this->_right_rotate(node);
						}
						this->_left_rotate(node->parent->parent);
						this->_recolour(node->parent);
						this->_recolour(node->parent->left);
					}
				}
			}
		}

		/*______________________________*/
		/*--- ERASE HELPER FUNCTIONS ---*/
		/*------------------------------*/

		/* this function handles all 3 cases, node is leafnode, node has	*/
		/* one child and node has two children								*/
		void	_delete_node(node_pointer &	node)
		{
			// print_i();
			// std::cout << "_----------------------------------_" << std::endl;
			node_pointer	helper = NULL;
			// print_p();
			/* CASE 1 - Node is leafnode 		*/
			if (this->_is_leafnode(node))
			{
				this->_delete_leafnode(node);
				this->_size--;
			}
			else
			{
				/* CASE 2 - Node has one child 		*/
				if (this->_has_one_child(node))
					helper = this->_get_single_child(node);
				/* CASE 3 - Node has two children 		*/
				else
					helper = this->_predecessor(node);
				/* SWAP node postion with child for for CASE 2	*/
				/* and with _predecessor for CASE 3 				*/
				this->_swap_nodes(node, helper);
				/* Updated tree will be checked again 	*/
				this->_delete_node(node);
			}
		}

		/* If a red node or root node is a leafnode it will definitely be	*/
		/* cleared without restructuring the tree 							*/
		/* If the rootnode is black, it will be deleted and the doubleblack	*/
		/* needs to be dissolved											*/
		void	_delete_leafnode(node_pointer const &	node)
		{
			/* CASE 1.1 - Leafnode is red 		*/
			if (node->colour == RED)
				this->_clear_node(node);
			/* CASE 1.2 - Leafnode is root 		*/
			else if (node == this->_root)
			{
				this->_root = this->_nil;
				this->_min = this->_root;
			 	this->_set_max(this->_root);
				this->_clear_node(node);
			}
			/* CASE 1.3 - Leafnode is black 		*/
			/* Node will be cleared and treated		*/
			/* as doubleblack, which will need to	*/
			/* be resolved in _dissolve_doubleblack	*/
			else if (node->colour == BLACK)
			{
				node_pointer	sibling = this->_get_sibling(node);
				node_pointer	parent = node->parent;
				
				this->_clear_node(node);
				this->_dissolve_doubleblack(parent, sibling);
			}
			this->_set_extrema();
		}

		/* Restructures the tree after deletion of black leafnode	*/
		void	_dissolve_doubleblack(node_pointer const &	parent, node_pointer const &	sibling)
		{
			// if (parent == this->_root)
			// 	return ;
			node_pointer helper = NULL;
			/* CASE 1 - Sibling of doubleblack node is red and	*/
			/* its two children are both black 					*/
			if (sibling->colour == RED && sibling->left->colour == BLACK && sibling->right->colour == BLACK) 
			{
				/* CASE 1.1 - Sibling is left child				*/
				/* right rotate the parent and _recolour sibling	*/
				/* and parent									*/
				if (this->_is_left_child(sibling))
				{
					helper = sibling->right;
					this->_right_rotate(parent);
				}
				/* CASE 1.2 - Sibling is right child			*/
				/* left rotate the parent and _recolour sibling	*/
				/* and parent, then doublblack node is kept		*/
				/* but new sibling is usd for dissolving DB		*/
				else
				{
					helper = sibling->left;
					this->_left_rotate(parent);
				}
				this->_recolour(sibling);
				this->_recolour(parent);
				this->_dissolve_doubleblack(parent, helper); 
			}
			/* CASE 2 - Sibling of doubleblack node is black 	*/
			/* and its two children are both black				*/
			else if (sibling->colour == BLACK && sibling->left->colour == BLACK && sibling->right->colour == BLACK)
			{
				/* CASE 2.1 - Parent of doubleblack is red	 	*/
				/* _recolour parent and sibling				 	*/
				this->_recolour(sibling);
				if (parent->colour == RED)
					this->_recolour(parent);
				/* CASE 2.2 - Parent of doubleblack is black	*/
				/* _recolour sibling	and handle parent as 		*/
				/* doubleblack node							 	*/
				else if (parent != this->_root)
					this->_dissolve_doubleblack(parent->parent, _get_sibling(parent)); // doubleblack status gets passed to parent and tree gets reorganised again
			}
			/* CASE 3 - Sibling of doubleblack node is black 		*/
			/* and one or both children are red						*/
			else if (sibling->colour == BLACK)
			{
				/* CASE 3.1 - Sibling is a right child	 			*/
				if (this->_is_right_child(sibling))
				{
					/* CASE 3.1.1 - Right child	of sibling is red	*/
					/* left rotate the parent and _recolour the 	*/
					/* sibling										*/
					if (sibling->right->colour == RED)
					{
						
						helper = sibling->right;
						if (parent->colour != sibling->colour)
						{
							this->_recolour(sibling);
							this->_recolour(parent);
						}
						this->_left_rotate(parent);
						this->_recolour(helper);
					}
					/* CASE 3.1.2 - Left child	of sibling is red	*/
					/* 1. right rotate left child of sibling		*/
					/* and _recolour sibling & left child			*/
					/* 2. left rotate the doubleblack nodes parent	*/
					/* and _recolour the sibling						*/
					else if (sibling->left->colour == RED)
					{
						helper = sibling->left;
						this->_recolour(helper);
						this->_recolour(sibling);
						this->_right_rotate(sibling);
						_dissolve_doubleblack(parent, parent->right);
					}
				}
				/* CASE 3.2 - Sibling is a left child	 			*/
				else if (this->_is_left_child(sibling))
				{
					/* CASE 3.2.1 - Left child	of sibling is red	*/
					/* Right rotate the parent and _recolour the 	*/
					/* sibling										*/
					if (sibling->left->colour == RED)
					{
						helper = sibling->left;
						if (parent->colour != sibling->colour)
						{
							this->_recolour(sibling);
							this->_recolour(parent);
						}
						this->_right_rotate(parent);
						this->_recolour(helper);
					}
					/* CASE 3.2.2 - Right child	of sibling is red	*/
					/* 1. left rotate right child of sibling		*/
					/* and _recolour sibling & right child			*/
					/* 2. right rotate the doubleblack nodes parent	*/
					/* and _recolour the sibling						*/
					else if (sibling->right->colour == RED)
					{
						helper = sibling->right;
						this->_recolour(helper);
						this->_recolour(sibling);
						this->_left_rotate(sibling);
						this->_dissolve_doubleblack(parent, parent->left);
					}
				}
			}
		}

		/*_________________________*/
		/*--- NODE MANIPULATION ---*/
		/*-------------------------*/

		void	_recolour(node_pointer const & node)
		{
			if (!node->null_node)
				node->colour = !node->colour;
		}

				void	_swap_nodes(node_pointer & node1, node_pointer & node2)
		{
			node_pointer	helper = this->_alloc.allocate(1);
			this->_alloc.construct(helper, node_type());

				this->_swap_parents_children(node1, node2);
			this->_swap_childrens_parents(node2, node1);

			helper->parent = node1->parent;
			helper->left = node1->left;
			helper->right = node1->right;
			helper->colour = node1->colour;

			if (node2->parent != node1)
				node1->parent = node2->parent;
			else
				node1->parent = node2;
			node1->left = node2->left;
			node1->right = node2->right;
			node1->colour = node2->colour;

			node2->parent = helper->parent;
			node2->left = helper->left;
			node2->right = helper->right;
			node2->colour = helper->colour;

			if (!node2->left->null_node)
				node2->left->parent = node2;
			if (!node2->right->null_node)
				node2->right->parent = node2;

			this->_clear_node(helper);
		}

		void	_swap_parents_children(node_pointer &	node1, node_pointer &	node2)
		{
			if (node1->parent == NULL)
				this->_root = node2;
			else if (node1->parent->left == node1)
					node1->parent->left = node2;
			else if (node1->parent->right == node1)
					node1->parent->right = node2;

			if (node2->parent->left == node2)
					node2->parent->left = node1;
			else if (node2->parent->right == node2)
					node2->parent->right = node1;
		}

		void	_swap_childrens_parents(node_pointer &	node1, node_pointer &	node2)
		{
				if (!node1->left->null_node)
					node1->left->parent = node2;
				if (!node1->right->null_node)
					node1->right->parent = node2;
		}

		/*_______________*/
		/*--- EXTREMA ---*/
		/*---------------*/

		/* Returns smalest valued node of a subtree		*/
		node_pointer	_minimum(node_pointer	node)
		{
			while (!node->null_node && !node->left->null_node)
				node = node->left;
			return node;
		}

		const node_pointer	_minimum(node_pointer	const node) const
		{
			while (!node->null_node && !node->left->null_node)
				node = node->left;
			return node;
		}

		/* Returns biggest valued node of a subtree		*/
		node_pointer	_maximum(node_pointer	node)
		{
			while (!node->null_node && !node->right->null_node)
				node = node->right;
			return node;
		}

		const node_pointer	_maximum(node_pointer	const node) const
		{
			while (!node->null_node && !node->right->null_node)
				node = node->right;
			return node;
		}

		/* Changes min/max after deletion */
		void	_set_extrema()
		{
			this->_set_max(_maximum(this->_root));
			this->_min = this->_minimum(this->_root);
		}

		void	_set_max(node_pointer const & node)
		{
			this->_max = node;
			this->_nil->parent = this->_max;
		}

		/* Checks if new min/max need to be reassigned after insertion */
		void	_insert_extrema(node_pointer node)
		{
			if (this->_is_smaller(node->content, this->_min->content))
				this->_min = node;
			else if (this->_is_greater(node->content, this->_max->content))
				this->_set_max(node);
		}

		/*___________________*/
		/*--- CLEAR NODES ---*/
		/*-------------------*/

		void	_clear_subtree(node_pointer node)
		{
			if (node->null_node)
				return;
			this->_clear_subtree(node->left);
			this->_clear_subtree(node->right);
			this->_alloc.destroy(node);
			this->_alloc.deallocate(node, 1);
			node = NULL;
		}

		void	_clear_node(node_pointer	node)
		{
			if (node->parent)
			{
				if (this->_is_left_child(node))
					node->parent->left = this->_nil;
				else if (this->_is_right_child(node))
					node->parent->right = this->_nil;
			}
			this->_alloc.destroy(node);
			this->_alloc.deallocate(node, 1);
		}


		/*______________________*/
		/*--- DEBUG PRINTING ---*/
		/*----------------------*/

		// # define COLOR_DEFAULT "\033[0m"
		// # define COLOR_RED "\033[31;1m"

		// void	_print_p() const
		// {
		// 	this->print_pair(this->_root, 0);
		// }

		// void	_print_i() const
		// {
		// 	this->print_int(this->_root, 0);
		// }

		// void _print_int(node_pointer node, size_type depth) const
		// {
		// 	for (size_t i = 0; i < depth; ++i)
		// 		std::cout << "    ";

		// 	if (!node->null_node)
		// 	{
		// 		if (this->_is_right_child(node))
		// 			std::cout << "⇗";
		// 		else
		// 			std::cout << "⇘";
		// 		if (!node->colour)
		// 			std::cout << COLOR_RED;
		// 		std::cout << "[" << node->content << "]\n" << COLOR_DEFAULT;
		// 	}

		// 	if (!node->null_node && !node->right->null_node)
		// 		this->print_int(node->right, depth +1);
		// 	else
		// 	{
		// 		for (size_t i = 0; i < depth + 1; ++i)
		// 			std::cout << "    ";
		// 		std::cout << "⇗[NULL]\n";
		// 	}

		// 	if (!node->null_node && !node->left->null_node)
		// 		this->print_int(node->left, depth +1);
		// 	else
		// 	{
		// 		for (size_t i = 0; i < depth + 1; ++i)
		// 			std::cout << "    ";
		// 		std::cout << "⇘[NULL]\n";
		// 	}
		// }
		// void _print_pair(node_pointer node, size_type depth) const
		// {
		// 	for (size_t i = 0; i < depth; ++i)
		// 		std::cout << "    ";

		// 	if (!node->null_node)
		// 	{
		// 		if (this->_is_right_child(node))
		// 			std::cout << "⇗";
		// 		else
		// 			std::cout << "⇘";
		// 		if (!node->colour)
		// 			std::cout << COLOR_RED;
		// 		std::cout << "[" << node->content.first << "]\n" << COLOR_DEFAULT;
		// 	}

		// 	if (!node->null_node && !node->right->null_node)
		// 		this->print_pair(node->right, depth +1);
		// 	else
		// 	{
		// 		for (size_t i = 0; i < depth + 1; ++i)
		// 			std::cout << "    ";
		// 		std::cout << "⇗[NULL]\n";
		// 	}

		// 	if (!node->null_node && !node->left->null_node)
		// 		this->print_pair(node->left, depth +1);
		// 	else
		// 	{
		// 		for (size_t i = 0; i < depth + 1; ++i)
		// 			std::cout << "    ";
		// 		std::cout << "⇘[NULL]\n";
		// 	}
		// }
	};
}

#endif