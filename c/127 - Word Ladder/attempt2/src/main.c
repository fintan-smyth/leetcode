/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:53:11 by fsmyth            #+#    #+#             */
/*   Updated: 2026/03/05 16:38:42 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef DEBUG
	#define ASSERT_QUEUE_POP() assert(q->size > 0 && "Popping empty queue!")
#else
	#define ASSERT_QUEUE_POP() do {} while (0)
#endif

// ### Generic Double Ended Queue (Linked list implementation) ###
//
#define FS_DECLARE_QUEUE(T, tag)                                                       \
                                                                                       \
typedef struct Queue_##tag##_node                                                      \
{                                                                                      \
	struct Queue_##tag##_node	*next;                                                 \
	struct Queue_##tag##_node	*prev;                                                 \
	T							val;                                                   \
}	Queue_##tag##_node;                                                                \
                                                                                       \
typedef struct Queue_##tag                                                             \
{                                                                                      \
	Queue_##tag##_node 	*head;                                                         \
	size_t				size;                                                          \
}	Queue_##tag;                                                                       \
                                                                                       \
static inline Queue_##tag *queue_##tag##_init(void)                                    \
{                                                                                      \
	return calloc(1, sizeof(Queue_##tag));                                             \
}                                                                                      \
                                                                                       \
static inline void queue_##tag##_push_head(Queue_##tag *q, T val)                      \
{                                                                                      \
	Queue_##tag##_node *new = calloc(1, sizeof(*new));                                 \
                                                                                       \
	new->val = val;                                                                    \
	if (q->head == NULL)                                                               \
	{                                                                                  \
		new->next = new;                                                               \
		new->prev = new;                                                               \
		q->head = new;                                                                 \
		q->size++;                                                                     \
		return ;                                                                       \
	}                                                                                  \
	Queue_##tag##_node *tmp = q->head->prev;                                           \
	new->next = q->head;                                                               \
	q->head->prev = new;                                                               \
	new->prev = tmp;                                                                   \
	tmp->next = new;                                                                   \
	q->head = new;                                                                     \
	q->size++;                                                                         \
}                                                                                      \
                                                                                       \
static inline void queue_##tag##_push_tail(Queue_##tag *q, T val)                      \
{                                                                                      \
	Queue_##tag##_node *new = calloc(1, sizeof(*new));                                 \
                                                                                       \
	new->val = val;                                                                    \
	if (q->head == NULL)                                                               \
	{                                                                                  \
		new->next = new;                                                               \
		new->prev = new;                                                               \
		q->head = new;                                                                 \
		q->size++;                                                                     \
		return ;                                                                       \
	}                                                                                  \
	Queue_##tag##_node *tmp = q->head->prev;                                           \
	new->next = q->head;                                                               \
	q->head->prev = new;                                                               \
	new->prev = tmp;                                                                   \
	tmp->next = new;                                                                   \
	q->size++;                                                                         \
}                                                                                      \
                                                                                       \
static inline T queue_##tag##_pop_head(Queue_##tag *q)                                 \
{                                                                                      \
	ASSERT_QUEUE_POP();                                                                \
	T out = q->head->val;                                                              \
                                                                                       \
	if (q->size <= 1)                                                                  \
	{                                                                                  \
		free(q->head);                                                                 \
		q->head = NULL;                                                                \
		q->size = 0;                                                                   \
		return out;                                                                    \
	}                                                                                  \
                                                                                       \
	Queue_##tag##_node *head = q->head;                                                \
	head->prev->next = head->next;                                                     \
	head->next->prev = head->prev;                                                     \
	q->head = head->next;                                                              \
	free(head);                                                                        \
	q->size--;                                                                         \
	return out;                                                                        \
}                                                                                      \
                                                                                       \
static inline T queue_##tag##_pop_tail(Queue_##tag *q)                                 \
{                                                                                      \
	ASSERT_QUEUE_POP();                                                                \
	T out = q->head->prev->val;                                                        \
                                                                                       \
	if (q->size <= 1)                                                                  \
	{                                                                                  \
		free(q->head);                                                                 \
		q->head = NULL;                                                                \
		q->size = 0;                                                                   \
		return out;                                                                    \
	}                                                                                  \
                                                                                       \
	Queue_##tag##_node *tail = q->head->prev;                                          \
	tail->next->prev = tail->prev;                                                     \
	tail->prev->next = tail->next;                                                     \
	free(tail);                                                                        \
	q->size--;                                                                         \
	return out;                                                                        \
}                                                                                      \
                                                                                       \
static inline void queue_##tag##_clear(Queue_##tag *q, void (*del)(T))                 \
{                                                                                      \
	if (del != NULL)                                                                   \
	{                                                                                  \
		while (q->size > 0)                                                            \
			del(queue_##tag##_pop_head(q));                                            \
	}                                                                                  \
	else                                                                               \
	{                                                                                  \
		while (q->size > 0)                                                            \
			queue_##tag##_pop_head(q);                                                 \
	}                                                                                  \
}                                                                                      \


typedef enum { RBT_RED = 0, RBT_BLACK } RBTColor;

#define SAFE_CMP(X, Y) ((X > Y) - (X < Y))

#define FS_DECLARE_BSTSET(T, tag, cmp)                                                 \
                                                                                       \
                                                                                       \
typedef struct BSTSet_##tag##_node                                                     \
{                                                                                      \
	T							val;                                                   \
	RBTColor					col;                                                   \
	struct BSTSet_##tag##_node	*left;                                                 \
	struct BSTSet_##tag##_node	*right;                                                \
	struct BSTSet_##tag##_node	*parent;                                               \
}	BSTSet_##tag##_node;                                                               \
                                                                                       \
typedef struct BSTSet_##tag                                                            \
{                                                                                      \
	BSTSet_##tag##_node	*tree;                                                         \
	size_t				size;                                                          \
}	BSTSet_##tag;                                                                      \
                                                                                       \
static void _bstset_##tag##_depth_r(BSTSet_##tag##_node *node,                         \
									int depth, int *max)                               \
{                                                                                      \
	if (node == NULL)                                                                  \
		return ;                                                                       \
	if (depth > *max)                                                                  \
		*max = depth;                                                                  \
	_bstset_##tag##_depth_r(node->left, depth + 1, max);                               \
	_bstset_##tag##_depth_r(node->right, depth + 1, max);                              \
}                                                                                      \
                                                                                       \
static inline int _bstset_##tag##_depth(BSTSet_##tag *set)                             \
{                                                                                      \
	int depth = 0;                                                                     \
                                                                                       \
	_bstset_##tag##_depth_r(set->tree, 0, &depth);                                     \
	return depth;                                                                      \
}                                                                                      \
                                                                                       \
static int _bstset_##tag##_validate_r(BSTSet_##tag##_node *node)                       \
{                                                                                      \
	if (node == NULL)                                                                  \
		return 1;                                                                      \
                                                                                       \
	if (node->col == RBT_RED)                                                          \
	{                                                                                  \
		if ((node->left != NULL && node->left->col == RBT_RED)                         \
			|| (node->right != NULL && node->right->col == RBT_RED))                   \
		{                                                                              \
			dprintf(2, "RBT violation: multiple red nodes in a row\n");                \
			return -1;                                                                 \
		}                                                                              \
	}                                                                                  \
                                                                                       \
	int left_height = _bstset_##tag##_validate_r(node->left);                          \
	int right_height = _bstset_##tag##_validate_r(node->right);                        \
                                                                                       \
	if (left_height == -1 || right_height == -1                                        \
		|| (left_height != right_height                                                \
		&& dprintf(2, "RBT violation: black height mismatch\n"))                       \
	)                                                                                  \
		return -1;                                                                     \
                                                                                       \
	return (node->col == RBT_BLACK) ? left_height + 1 : left_height;                   \
}                                                                                      \
                                                                                       \
static inline bool bstset_##tag##_validate(BSTSet_##tag *set)                          \
{                                                                                      \
	if (set->tree == NULL)                                                             \
		return true;                                                                   \
                                                                                       \
	if (set->tree->col != RBT_BLACK)                                                   \
	{                                                                                  \
		dprintf(2, "RBT violation: root node is not black\n");                         \
		return false;                                                                  \
	}                                                                                  \
	                                                                                   \
	return (_bstset_##tag##_validate_r(set->tree) != -1);                              \
}                                                                                      \
                                                                                       \
static void _bstset_##tag##_print(BSTSet_##tag##_node *node, int space)                \
{                                                                                      \
    if (node == NULL) return;                                                          \
    space += 8;                                                                        \
    _bstset_##tag##_print(node->right, space);                                         \
	int i;                                                                             \
    for (i = 8; i < space - 6; i++) printf(" ");                                       \
    for (; i < space; i++) printf("-");                                                \
    printf("%s%3d\e[m\n", node->col == RBT_RED ? "\e[41;30m" : "\e[47;30m", node->val);\
    _bstset_##tag##_print(node->left, space);                                          \
}                                                                                      \
                                                                                       \
static inline BSTSet_##tag *bstset_##tag##_init()                                      \
{                                                                                      \
	BSTSet_##tag *set = calloc(1, sizeof(*set));                                       \
                                                                                       \
	return set;                                                                        \
}                                                                                      \
                                                                                       \
static inline BSTSet_##tag##_node *_bstset_##tag##_min(BSTSet_##tag##_node *node)      \
{                                                                                      \
	while (node->left != NULL)                                                         \
		node = node->left;                                                             \
	return node;                                                                       \
}                                                                                      \
                                                                                       \
static inline void _bstset_##tag##_transplant(BSTSet_##tag *set,                       \
												BSTSet_##tag##_node *dead,             \
												BSTSet_##tag##_node *node)             \
{                                                                                      \
	if (dead->parent == NULL)                                                          \
		set->tree = node;                                                              \
	else if (dead == dead->parent->left)                                               \
		dead->parent->left = node;                                                     \
	else                                                                               \
		dead->parent->right = node;                                                    \
	if (node != NULL)                                                                  \
		node->parent = dead->parent;                                                   \
}                                                                                      \
                                                                                       \
static inline void _bstset_##tag##_rotate_left(BSTSet_##tag *set,                      \
												BSTSet_##tag##_node *node)             \
{                                                                                      \
	BSTSet_##tag##_node *right = node->right;                                          \
                                                                                       \
	node->right = right->left;                                                         \
	if (right->left != NULL)                                                           \
		right->left->parent = node;                                                    \
                                                                                       \
	right->parent = node->parent;                                                      \
	if (node->parent == NULL)                                                          \
		set->tree = right;                                                             \
	else if (node == node->parent->left)                                               \
		node->parent->left = right;                                                    \
	else                                                                               \
		node->parent->right = right;                                                   \
                                                                                       \
	right->left = node;                                                                \
	node->parent = right;                                                              \
}                                                                                      \
                                                                                       \
static inline void _bstset_##tag##_rotate_right(BSTSet_##tag *set,                     \
												BSTSet_##tag##_node *node)             \
{                                                                                      \
	BSTSet_##tag##_node *left = node->left;                                            \
                                                                                       \
	node->left = left->right;                                                          \
	if (left->right != NULL)                                                           \
		left->right->parent = node;                                                    \
                                                                                       \
	left->parent = node->parent;                                                       \
	if (node->parent == NULL)                                                          \
		set->tree = left;                                                              \
	else if (node == node->parent->left)                                               \
		node->parent->left = left;                                                     \
	else                                                                               \
		node->parent->right = left;                                                    \
                                                                                       \
	left->right = node;                                                                \
	node->parent = left;                                                               \
}                                                                                      \
                                                                                       \
/* static inline void print_bstset_##tag(BSTSet_##tag *set) */                         \
                                                                                       \
static inline void _bstset_##tag##_balance_insert(BSTSet_##tag *set,                   \
													BSTSet_##tag##_node *node)         \
{                                                                                      \
	while (node->parent != NULL && node->parent->col == RBT_RED)                       \
	{                                                                                  \
		if (node->parent == node->parent->parent->left)                                \
		{                                                                              \
			BSTSet_##tag##_node *uncle = node->parent->parent->right;                  \
			if (uncle != NULL && uncle->col == RBT_RED)                                \
			{                                                                          \
				node->parent->col = RBT_BLACK;                                         \
				uncle->col = RBT_BLACK;                                                \
				node->parent->parent->col = RBT_RED;                                   \
				node = node->parent->parent;                                           \
			}                                                                          \
			else                                                                       \
			{                                                                          \
				if (node == node->parent->right)                                       \
				{                                                                      \
					node = node->parent;                                               \
					_bstset_##tag##_rotate_left(set, node);                            \
				}                                                                      \
				node->parent->col = RBT_BLACK;                                         \
				node->parent->parent->col = RBT_RED;                                   \
				_bstset_##tag##_rotate_right(set, node->parent->parent);               \
			}                                                                          \
		}                                                                              \
		else                                                                           \
		{                                                                              \
			BSTSet_##tag##_node *uncle = node->parent->parent->left;                   \
			if (uncle != NULL && uncle->col == RBT_RED)                                \
			{                                                                          \
				node->parent->col = RBT_BLACK;                                         \
				uncle->col = RBT_BLACK;                                                \
				node->parent->parent->col = RBT_RED;                                   \
				node = node->parent->parent;                                           \
			}                                                                          \
			else                                                                       \
			{                                                                          \
				if (node == node->parent->left)                                        \
				{                                                                      \
					node = node->parent;                                               \
					_bstset_##tag##_rotate_right(set, node);                           \
				}                                                                      \
				node->parent->col = RBT_BLACK;                                         \
				node->parent->parent->col = RBT_RED;                                   \
				_bstset_##tag##_rotate_left(set, node->parent->parent);                \
			}                                                                          \
		}                                                                              \
	}                                                                                  \
	set->tree->col = RBT_BLACK;                                                        \
}                                                                                      \
                                                                                       \
static inline int bstset_##tag##_insert(BSTSet_##tag *set, T val)                      \
{                                                                                      \
	BSTSet_##tag##_node *current = set->tree;                                          \
	BSTSet_##tag##_node *parent = NULL;                                                \
	int (*cmpf)(T, T) = (int (*)(T, T))cmp;                                            \
	int	diff = 0;                                                                      \
                                                                                       \
	while (current != NULL)                                                            \
	{                                                                                  \
		parent = current;                                                              \
		diff = (cmpf == NULL)                                                          \
			? SAFE_CMP(val, current->val)                                              \
			: cmpf(val, current->val);                                                 \
		if (diff > 0)                                                                  \
			current = current->right;                                                  \
		else if (diff < 0)                                                             \
			current = current->left;                                                   \
		else                                                                           \
			return 1;                                                                  \
	}                                                                                  \
                                                                                       \
	BSTSet_##tag##_node *new = calloc(1, sizeof(*new));                                \
	new->val = val;                                                                    \
	new->parent = parent;                                                              \
	if (parent == NULL)                                                                \
		set->tree = new;                                                               \
	else if (diff > 0)                                                                 \
		parent->right = new;                                                           \
	else                                                                               \
		parent->left = new;                                                            \
	set->size++;                                                                       \
                                                                                       \
	/* printf("\e[?25l");                                                                 \
	printf("\e[2J\e[H");                                                               \
	bstset_##tag##_print_rb(set);                                                      \
	getchar(); */                                                                         \
	_bstset_##tag##_balance_insert(set, new);                                          \
	/* printf("\e[2J\e[H");                                                               \
	bstset_##tag##_print_rb(set);                                                      \
	getchar();                                                                         \
	printf("\e[?25h"); */                                                                \
	                                                                                   \
	return 0;                                                                          \
}                                                                                      \
                                                                                       \
static inline void _bstset_##tag##_remove_fix(BSTSet_##tag *set,                       \
												BSTSet_##tag##_node *node,             \
												BSTSet_##tag##_node *parent)           \
{                                                                                      \
	while (node != set->tree && (node == NULL || node->col == RBT_BLACK))              \
	{                                                                                  \
		if (node == parent->left)                                                      \
		{                                                                              \
			BSTSet_##tag##_node *sibling = parent->right;                              \
			if (sibling == NULL)                                                       \
			{                                                                          \
				node = parent;                                                         \
				parent = node->parent;                                                 \
				continue ;                                                             \
			}                                                                          \
			if (sibling->col == RBT_RED)                                               \
			{                                                                          \
				sibling->col = RBT_BLACK;                                              \
				parent->col = RBT_RED;                                                 \
				_bstset_##tag##_rotate_left(set, parent);                              \
				sibling = parent->right;                                               \
				if (sibling == NULL)                                                   \
				{                                                                      \
					node = parent;                                                     \
					parent = node->parent;                                             \
					continue ;                                                         \
				}                                                                      \
			}                                                                          \
                                                                                       \
			bool left_black = sibling->left == NULL || sibling->left->col == RBT_BLACK;\
			bool right_black = sibling->right == NULL || sibling->right->col == RBT_BLACK;\
                                                                                       \
			if (left_black && right_black)                                             \
			{                                                                          \
				sibling->col = RBT_RED;                                                \
				node = parent;                                                         \
				parent = node->parent;                                                 \
			}                                                                          \
			else                                                                       \
			{                                                                          \
				if (right_black)                                                       \
				{                                                                      \
					if (sibling->left != NULL)                                         \
						sibling->left->col = RBT_BLACK;                                \
					sibling->col = RBT_RED;                                            \
					_bstset_##tag##_rotate_right(set, sibling);                        \
					sibling = parent->right;                                           \
				}                                                                      \
				sibling->col = parent->col;                                            \
				parent->col = RBT_BLACK;                                               \
				if (sibling->right != NULL)                                            \
					sibling->right->col = RBT_BLACK;                                   \
				_bstset_##tag##_rotate_left(set, parent);                              \
				node = set->tree;                                                      \
			}                                                                          \
		}                                                                              \
		else                                                                           \
		{                                                                              \
			BSTSet_##tag##_node *sibling = parent->left;                               \
			if (sibling == NULL)                                                       \
			{                                                                          \
				node = parent;                                                         \
				parent = node->parent;                                                 \
				continue ;                                                             \
			}                                                                          \
			if (sibling->col == RBT_RED)                                               \
			{                                                                          \
				sibling->col = RBT_BLACK;                                              \
				parent->col = RBT_RED;                                                 \
				_bstset_##tag##_rotate_right(set, parent);                             \
				sibling = parent->left;                                                \
				if (sibling == NULL)                                                   \
				{                                                                      \
					node = parent;                                                     \
					parent = node->parent;                                             \
					continue ;                                                         \
				}                                                                      \
			}                                                                          \
                                                                                       \
			bool left_black = sibling->left == NULL || sibling->left->col == RBT_BLACK;\
			bool right_black = sibling->right == NULL || sibling->right->col == RBT_BLACK;\
                                                                                       \
			if (left_black && right_black)                                             \
			{                                                                          \
				sibling->col = RBT_RED;                                                \
				node = parent;                                                         \
				parent = node->parent;                                                 \
			}                                                                          \
			else                                                                       \
			{                                                                          \
				if (left_black)                                                        \
				{                                                                      \
					if (sibling->right != NULL)                                        \
						sibling->right->col = RBT_BLACK;                               \
					sibling->col = RBT_RED;                                            \
					_bstset_##tag##_rotate_left(set, sibling);                         \
					sibling = parent->left;                                            \
				}                                                                      \
				sibling->col = parent->col;                                            \
				parent->col = RBT_BLACK;                                               \
				if (sibling->left != NULL)                                             \
					sibling->left->col = RBT_BLACK;                                    \
				_bstset_##tag##_rotate_right(set, parent);                             \
				node = set->tree;                                                      \
			}                                                                          \
		}                                                                              \
	}                                                                                  \
	if (node != NULL)                                                                  \
		node->col = RBT_BLACK;                                                         \
}                                                                                      \
                                                                                       \
static inline int bstset_##tag##_remove(BSTSet_##tag *set, T val, void (*del)(T))      \
{                                                                                      \
	BSTSet_##tag##_node *target = set->tree;                                           \
	int (*cmpf)(T, T) = (int (*)(T, T))cmp;                                            \
	while (target != NULL)                                                             \
	{                                                                                  \
		int diff = (cmpf == NULL)                                                      \
			? SAFE_CMP(val, target->val)                                               \
			: cmpf(val, target->val);                                                  \
		if (diff == 0)                                                                 \
			break ;                                                                    \
		target = diff < 0 ? target->left : target->right;                              \
	}                                                                                  \
	if (target == NULL)                                                                \
		return 1;                                                                      \
                                                                                       \
	BSTSet_##tag##_node *replacement = NULL;                                           \
	BSTSet_##tag##_node *to_fix = NULL;                                                \
	BSTSet_##tag##_node *fix_parent;                                                   \
	RBTColor orig_col = target->col;                                                   \
                                                                                       \
	if (target->left == NULL)                                                          \
	{                                                                                  \
		to_fix = target->right;                                                        \
		fix_parent = target->parent;                                                   \
		_bstset_##tag##_transplant(set, target, target->right);                        \
	}                                                                                  \
	else if (target->right == NULL)                                                    \
	{                                                                                  \
		to_fix = target->left;                                                         \
		fix_parent = target->parent;                                                   \
		_bstset_##tag##_transplant(set, target, target->left);                         \
	}                                                                                  \
	else                                                                               \
	{                                                                                  \
		replacement = _bstset_##tag##_min(target->right);                              \
		orig_col = replacement->col;                                                   \
		to_fix = replacement->right;                                                   \
                                                                                       \
		if (replacement->parent == target)                                             \
		{                                                                              \
			fix_parent = replacement;                                                  \
		}                                                                              \
		else                                                                           \
		{                                                                              \
			fix_parent = replacement->parent;                                          \
			_bstset_##tag##_transplant(set, replacement, replacement->right);          \
			replacement->right = target->right;                                        \
			replacement->right->parent = replacement;                                  \
		}                                                                              \
		_bstset_##tag##_transplant(set, target, replacement);                          \
		replacement->left = target->left;                                              \
		replacement->left->parent = replacement;                                       \
		replacement->col = target->col;                                                \
	}                                                                                  \
                                                                                       \
	if (orig_col == RBT_BLACK)                                                         \
		_bstset_##tag##_remove_fix(set, to_fix, fix_parent);                           \
                                                                                       \
	if (set->tree != NULL)                                                             \
		set->tree->col = RBT_BLACK;                                                    \
                                                                                       \
    if (del != NULL)                                                                   \
		del(target->val);                                                              \
	free(target);                                                                      \
	set->size--;                                                                       \
	return 0;                                                                          \
}                                                                                      \
                                                                                       \
static inline int bstset_##tag##_contains(BSTSet_##tag *set, T val)                    \
{                                                                                      \
	BSTSet_##tag##_node *current = set->tree;                                          \
	int (*cmpf)(T, T) = (int (*)(T, T))cmp;                                            \
                                                                                       \
	while (current != NULL)                                                            \
	{                                                                                  \
		int diff = (cmpf == NULL)                                                      \
			? SAFE_CMP(val, current->val)                                              \
			: cmpf(val, current->val);                                                 \
		if (diff > 0)                                                                  \
			current = current->right;                                                  \
		else if (diff < 0)                                                             \
			current = current->left;                                                   \
		else                                                                           \
			return true;                                                               \
	}                                                                                  \
                                                                                       \
	return false;                                                                      \
}                                                                                      \
                                                                                       \
static void _bstset_##tag##_clear_r(BSTSet_##tag##_node *node, void (*del)(T))         \
{                                                                                      \
	if (node == NULL)                                                                  \
		return ;                                                                       \
	_bstset_##tag##_clear_r(node->left, del);                                          \
	_bstset_##tag##_clear_r(node->right, del);                                         \
	if (del != NULL)                                                                   \
		del(node->val);                                                                \
	free(node);                                                                        \
}                                                                                      \
                                                                                       \
static inline void bstset_##tag##_clear(BSTSet_##tag *set, void (*del)(T))             \
{                                                                                      \
	_bstset_##tag##_clear_r(set->tree, del);                                           \
	set->tree = NULL;                                                                  \
	set->size = 0;                                                                     \
}                                                                                      \

FS_DECLARE_BSTSET(char *, str, strcmp);
FS_DECLARE_QUEUE(char *, str);

int ladderLength(char* beginWord, char* endWord, char** wordList, int wordListSize)
{
	BSTSet_str set = {};
	for (int i = 0; i < wordListSize; i++)
		bstset_str_insert(&set, wordList[i]);

	if (!bstset_str_contains(&set, endWord))
	{
		return 0;
	}

	int len = strlen(beginWord);
	char *tmp = malloc(len + 1);
	int	depth = 0;
	Queue_str *q = queue_str_init();

	queue_str_push_head(q, strdup(beginWord));
	while (q->size > 0)
	{
		depth++;
		int n = q->size;
		while (n--)
		{
			char *cur = queue_str_pop_tail(q);
			for (int i = 0; i < len; i++)
			{
				strcpy(tmp, cur);
				for (char c = 'a'; c <= 'z'; c++)
				{
					tmp[i] = c;
					if (strcmp(tmp, cur) == 0)
						continue ;
					if (strcmp(tmp, endWord) == 0)
					{
						bstset_str_clear(&set, NULL);
						queue_str_clear(q, (void (*)(char *))free);
						free(q);
						free(tmp);
						free(cur);
						return depth + 1;
					}
					if (bstset_str_contains(&set, tmp))
					{
						queue_str_push_head(q, strdup(tmp));
						bstset_str_remove(&set, tmp, NULL);
					}
				}
			}
			free(cur);
		}
	}
	return (0);
}

// int main(int argc, char **argv)
// {
// 	if (argc < 3)
// 		printf("Insufficient args\n"), exit(1);
//
// 	int min = ladderLength(argv[1], argv[2], &argv[3], argc - 3);
// 	printf("shortest %s->%s: %d\n", argv[1], argv[2], min);
// }
