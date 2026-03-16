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
#include <stdbool.h>
#include <string.h>

typedef struct TrieNode
{
	char			c;
	char			*word;
	bool			found;
	struct TrieNode	*children[26];
}	TrieNode;

TrieNode	*new_trienode(char c)
{
	TrieNode *new = calloc(1, sizeof(TrieNode));

	new->c = c;
	return new;
}

void	trie_add_word(char *word, TrieNode *head)
{
	TrieNode *current = head;

	for (int i = 0; word[i] != '\0'; i++)
	{
		char	c = word[i];
		int		idx = c - 'a';

		if (current->children[idx] == NULL)
			current->children[idx] = new_trienode(c);
		current = current->children[idx];
	}
	current->word = word;
}

TrieNode	*build_trie(char **words, int words_size)
{
	TrieNode *head = new_trienode(0);

	for (int i = 0; i < words_size; i++)
		trie_add_word(words[i], head);

	return head;
}

void	print_trie(TrieNode *node)
{
	if (node == NULL)
		return ;

	if (node->word != NULL)
		printf("%s\n", node->word);

	for (int i = 0; i < 26; i++)
	{
		print_trie(node->children[i]);
	}
}

void	explore_board(char **board, int x, int y, char **found, int *foundsize, TrieNode *current, int boardSize, int *boardColSize)
{
	if (current == NULL)
		return ;

	if (current->word != NULL && !current->found)
	{
		found[(*foundsize)++] = current->word;
		current->found = true;
		// hashset_insert(set, current->word);
	}

	char saved = board[y][x];
	board[y][x] = 0;
	if (y > 0)
	{
		char c = board[y - 1][x];
		if (c != 0)
			explore_board(board, x, y - 1, found, foundsize, current->children[c - 'a'], boardSize, boardColSize);
	}
	if (x > 0)
	{
		char c = board[y][x - 1];
		if (c != 0)
			explore_board(board, x - 1, y, found, foundsize, current->children[c - 'a'], boardSize, boardColSize);
	}
	if (y < boardSize - 1)
	{
		char c = board[y + 1][x];
		if (c != 0)
			explore_board(board, x, y + 1, found, foundsize, current->children[c - 'a'], boardSize, boardColSize);
	}
	if (x < boardColSize[y] - 1)
	{
		char c = board[y][x + 1];
		if (c != 0)
			explore_board(board, x + 1, y, found, foundsize, current->children[c - 'a'], boardSize, boardColSize);
	}
	board[y][x] = saved;
}

char **copy_board(char **board, int boardSize, int *boardColSize)
{
	char		**board_copy = calloc(boardSize, sizeof(char *));
	for (int i = 0; i < boardSize; i++)
	{
		board_copy[i] = calloc(boardColSize[i], sizeof(char));
		memcpy(board_copy[i], board[i], boardColSize[i]);
	}
	return board_copy;
}

void free_board_copy(char **board, int boardSize)
{
	for (int i = 0; i < boardSize; i++)
		free(board[i]);
	free(board);
}

char	**findWords(char** board, int boardSize, int* boardColSize, char** words, int wordsSize, int* returnSize)
{
	TrieNode	*head = build_trie(words, wordsSize);
	char **board_copy = copy_board(board, boardSize, boardColSize);
	char **found = calloc(wordsSize, sizeof(char *));
	int	foundsize = 0;

	print_trie(head);

	for (int y = 0; y < boardSize; y++)
	{
		for (int x = 0; x < boardColSize[y]; x++)
		{
			char c = board_copy[y][x];

			explore_board(board_copy, x, y, found, &foundsize, head->children[c - 'a'], boardSize, boardColSize);

		}
	}
	free_board_copy(board_copy, boardSize);

	// printf("set size: %d\n", set.size);
	// print_set(set.set);

	// char **out = set_to_array(&set);
	*returnSize = foundsize;

	return found;
}

// int main(void)
// {
// 	char *words[] = {
// 		"oath",
// 		"pea",
// 		"eat",
// 		"rain",
// 		"hklf",
// 		"hf",
// 	};
// 	char *board[] = {
// 		"oaan",
// 		"etae",
// 		"ihkr",
// 		"iflv",
// 	};
// 	int	boardSize = 4;
// 	int	boardColSize[4] = {4, 4, 4, 4};
// 	int returnSize = 0;
// 	int wordsSize = 6;
//
// 	char **ret = findWords(board, boardSize, boardColSize, words, wordsSize, &returnSize);
//
// 	printf("-------------------------\n");
// 	for (int i = 0; i < returnSize; i++)
// 		printf("%s\n", ret[i]);
// }
