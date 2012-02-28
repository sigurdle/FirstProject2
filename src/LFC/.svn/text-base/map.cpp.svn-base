#include "stdafx.h"
#include "LFC.h"

namespace System
{

void left_rotate(red_black_node_base** tree, red_black_node_base* x)
{
	red_black_node_base* y = x->right;

	x->right = y->left;
	if (y->left != NULL) y->left->parent = x;

	y->parent = x->parent;
	if (x == *tree)
	{
		*tree = y;
	}
	else
	{
		if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}

	y->left = x;
	x->parent = y;
}

void right_rotate(red_black_node_base** tree, red_black_node_base* y)
{
	red_black_node_base* _x = y->left;

	y->left = _x->right;
	if (_x->right != NULL) _x->right->parent = y;

	_x->parent = y->parent;
	if (y == *tree)
	{
		*tree = _x;
	}
	else
	{
		if (y == y->parent->left)
		{
			y->parent->left = _x;
		}
		else
		{
			y->parent->right = _x;
		}
	}

	_x->right = y;
	y->parent = _x;
}

static void balance(red_black_node_base** tree, red_black_node_base* x)
{
	while (x != *tree && x->parent->color == Red)
	{
	// If x's parent is a left, y is x's right 'uncle'
		if (x->parent == x->parent->parent->left)
		{
			red_black_node_base* y = x->parent->parent->right;

			if (y && y->color == Red)	// case 1
			{
				// recolor
				x->parent->color = Black;
				x->parent->parent->color = Red;
				y->color = Black;

				// Move x up the tree
				x = x->parent->parent;
			}
			else
			{
				if ( x == x->parent->right )
				{
					/* and x is to the right */ 
					/* case 2 - move x up and rotate */
					x = x->parent;
					left_rotate(tree, x );
				}
				/* case 3 */
				x->parent->color = Black;
				x->parent->parent->color = Red;
				right_rotate(tree, x->parent->parent );
			}
		}
		else
		{
		// repeat the "if" part with right and left exchanged

			red_black_node_base* y = x->parent->parent->left;

			if (y && y->color == Red)	// case 1
			{
				// recolor
				x->parent->color = Black;
				x->parent->parent->color = Red;
				y->color = Black;

				// Move x up the tree
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->left)
				{
					/* and x is to the right */ 
					/* case 2 - move x up and rotate */
					x = x->parent;
					right_rotate(tree, x );
				}
				/* case 3 */
				x->parent->color = Black;
				x->parent->parent->color = Red;
				left_rotate(tree, x->parent->parent);
			}
		}
	}
}

/*
rb_tree_base::rb_tree_base()
{
	m_size = 0;

	head = new red_black_node_base;
	head->color = Red;
	head->parent = NULL;	// root
	head->left = head;	// leftmost
	head->right = head;	// rightmost
}

rb_tree_base::~rb_tree_base()
{
	delete head;
}
*/

void rb_tree_base::balance(red_black_node_base* x)
{
	System::balance(&head->parent, x);
}

void rb_tree_iterator::Inc()
{
	if (m_p->right != NULL)
	{
		m_p = leftmost(m_p->right);
	}
	else
	{
		red_black_node_base * parent;

		while (m_p == (parent = m_p->parent)->right)
		{
			m_p = parent;
		}

		if (m_p->right != parent)
		{
			m_p = parent;
		}
	}
}

}
