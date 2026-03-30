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
#include <stdio.h>
#include <stdbool.h>

struct TreeNode
{
	int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int min = INT_MAX;
int *prev = NULL;

void	get_diff_r(struct TreeNode *node)
{
	if (node->left)
		get_diff_r(node->left);
	
	int diff = (prev == NULL) ? INT_MAX : node->val - *prev;
	if (diff < min)
		min = diff;
	
	prev = &node->val;
	if (node->right)
		get_diff_r(node->right);
}

int getMinimumDifference(struct TreeNode* root)
{
	get_diff_r(root);
	return min;
}

int	main(void)
{
	struct TreeNode nodes[3] = {};

	nodes[0].val = 5;
	nodes[0].left = &nodes[1];
	nodes[0].right = &nodes[2];
	nodes[1].val = 4;
	nodes[2].val = 7;

	printf("min: %d\n", getMinimumDifference(&nodes[0]));
}
