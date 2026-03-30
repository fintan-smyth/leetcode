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
#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

// int maxPathSum(struct TreeNode* root) {
//
// }

struct TreeNode *treenode_new(int val)
{
	struct TreeNode *out = calloc(1, sizeof(struct TreeNode));
	out->val = val;
	out->left = NULL;
	out->right = NULL;

	return out;
}

struct TreeNode *build_testcase(void)
{
	struct TreeNode *root = treenode_new(-10);

	root->left = treenode_new(9);
	root->right = treenode_new(20);
	root->right->left = treenode_new(15);
	root->right->right = treenode_new(7);

	return root;
}

void	clear_tree(struct TreeNode *root)
{
	if (root == NULL)
		return ;
	clear_tree(root->left);
	clear_tree(root->right);
	free(root);
}

int max_int(int a, int b)
{
	return a > b ? a : b;
}

int max_branch_sum(struct TreeNode *root)
{
	if (root == NULL)
		return 0;

	int max_left = max_branch_sum(root->left);
	int max_right = max_branch_sum(root->right);
	int max = max_int(max_left, max_right);
	return (root->val + max_int(0, max));
}

void	get_max_path_sum(struct TreeNode *root, int *max)
{
	if (root == NULL)
		return ;

	int path_sum = root->val;
	int max_left = max_branch_sum(root->left);
	int max_right = max_branch_sum(root->right);

	if (max_left > 0)
		path_sum += max_left;
	if (max_right > 0)
		path_sum += max_right;

	if (path_sum > *max)
		*max = path_sum;
	get_max_path_sum(root->left, max);
	get_max_path_sum(root->right, max);
}

int maxPathSum(struct TreeNode* root)
{
	int max = INT_MIN;

	get_max_path_sum(root, &max);
	return (max);
}

int	main(void)
{
	struct TreeNode *root = build_testcase();

	printf("max root: %d\n", max_branch_sum(root));
	printf("max left: %d\n", max_branch_sum(root->left));
	printf("max left: %d\n", max_branch_sum(root->right));

	printf("maxPathSum: %d\n", maxPathSum(root));

	clear_tree(root);
}
