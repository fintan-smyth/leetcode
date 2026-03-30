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

typedef struct AdjList
{
	struct GraphNode	*node;
	struct AdjList		*next;
}	AdjList;

typedef struct GraphNode
{
	char	*str;
	bool	visited;
	int		depth;
	AdjList	*neighbours;
}	GraphNode;

typedef struct Queue
{
	GraphNode *node;
	struct Queue *next;
	struct Queue *prev;
}	Queue;

typedef struct Map
{
	GraphNode	graphnode;
	struct Map	*left;
	struct Map	*right;
}	Map;

Map	*map_insert(Map **root, Map *new)
{
	if (root == NULL)
		return NULL;

	Map *current = *root;
	Map **addr = root;

	while (current != NULL)
	{
		int diff = strcmp(new->graphnode.str, current->graphnode.str);
		if (diff < 0)
			addr = &current->left;
		else if (diff > 0)
			addr = &current->right;
		else
			break ;
		current = *addr;
	}
	if (*addr != NULL)
	{
		// printf("Map node already exists: %s\n", (*addr)->graphnode.str), exit(1);
		free(new);
		return NULL;
	}
	*addr = new;
	return new;
}

void	clear_map(Map *map)
{
	if (map == NULL)
		return ;

	clear_map(map->left);
	clear_map(map->right);

	AdjList *current = map->graphnode.neighbours;
	while (current != NULL)
	{
		AdjList *tmp = current;
		current = current->next;
		free(tmp);
	}
	free(map);
}

void	queue_push(Queue **queue, GraphNode *node, int depth)
{
	Queue *new = calloc(1, sizeof(*new));
	Queue *head = *queue;

	new->node = node;
	node->depth = depth;
	node->visited = true;
	if (head == NULL)
	{
		*queue = new;
		new->next = new;
		new->prev = new;
		return ;
	}
	new->next = head;
	new->prev = head->prev;
	head->prev = new;
	new->prev->next = new;
	*queue = new;
}

GraphNode *queue_pop(Queue **queue)
{
	Queue *head = *queue;
	GraphNode *out = head->prev->node;

	if (head->prev == head)
	{
		*queue = NULL;
		free(head);
	}
	else
	{
		Queue *tail = head->prev->prev;
		free(head->prev);
		tail->next = head;
		head->prev = tail;
	}
	return out;
}

GraphNode *map_get(Map *root, char *str)
{
	if (root == NULL)
		return NULL;

	Map *current = root;
	int	diff = strcmp(str, current->graphnode.str);
	
	while (diff != 0)
	{
		if (diff < 0)
			current = current->left;
		else if (diff > 0)
			current = current->right;
		if (current == NULL)
			return NULL;
		diff = strcmp(str, current->graphnode.str);
	}
	return &current->graphnode;
}

void	print_map(Map *root)
{
	if (root == NULL)
		return ;

	print_map(root->left);
	printf("word: %s\n", root->graphnode.str);
	print_map(root->right);
}

void	graph_clear_visited(Map *root)
{
	if (root == NULL)
		return ;

	root->graphnode.visited = false;
	graph_clear_visited(root->left);
	graph_clear_visited(root->right);
}

void	graph_add_edge(GraphNode *first, GraphNode *second)
{
	AdjList *edge = calloc(1, sizeof(AdjList));
	edge->node = second;

	if (first->neighbours == NULL)
		first->neighbours = edge;
	else
	{
		AdjList *current = first->neighbours;
		while (current->next != NULL)
			current = current->next;
		current->next = edge;
	}
}

int	count_diff_chars(char *str1, char *str2)
{
	int count = 0;

	for (int i = 0; str1[i]; i++)
	{
		if (str1[i] != str2[i])
			count++;
	}

	return count;
}

void	connect_graph_node(Map *root, GraphNode *node)
{
	if (root == NULL)
		return ;

	if (count_diff_chars(root->graphnode.str, node->str) == 1)
	{
		graph_add_edge(&root->graphnode, node);
		graph_add_edge(node, &root->graphnode);
	}
	connect_graph_node(root->left, node);
	connect_graph_node(root->right, node);
}

void	print_graph(GraphNode *node, int depth)
{
	if (node->visited)
		return ;

	node->visited = true;
	printf("%*s%d: %s\n", depth, "", depth, node->str);

	AdjList *current = node->neighbours;
	while (current != NULL)
	{
		print_graph(current->node, depth + 1);
		current = current->next;
	}
}

int	get_shortest_path(GraphNode *start, char *end_str, Map *map)
{
	GraphNode *end = map_get(map, end_str);

	if (end == NULL)
		return 0;

	Queue *queue = NULL;
	queue_push(&queue, start, 1);

	while (queue != NULL)
	{
		GraphNode *current = queue_pop(&queue);
		if (current == end)
			return current->depth;
		AdjList *cur_neighbour = current->neighbours;
		while (cur_neighbour != NULL)
		{
			if (!cur_neighbour->node->visited)
				queue_push(&queue, cur_neighbour->node, current->depth + 1);
			cur_neighbour = cur_neighbour->next;
		}
	}
	return (0);
}

int ladderLength(char* beginWord, char* endWord, char** wordList, int wordListSize)
{
	Map *root = NULL;

	Map *new = calloc(1, sizeof(*new));
	GraphNode *start = &new->graphnode;
	new->graphnode.str = beginWord;
	map_insert(&root, new);
	connect_graph_node(root, &new->graphnode);

	for (int i = 0; i < wordListSize; i++)
	{
		new = calloc(1, sizeof(*new));
		new->graphnode.str = wordList[i];
		if (map_insert(&root, new))
			connect_graph_node(root, &new->graphnode);
	}

	// print_map(root);
	// print_graph(map_get(root, "sog"), 0);
	// graph_clear_visited(root);
	// print_graph(map_get(root, "lot"), 0);
	
	int min = get_shortest_path(start, endWord, root);
	clear_map(root);
	return min;
}

int main(int argc, char **argv)
{
	if (argc < 3)
		printf("Insufficient args\n"), exit(1);

	int min = ladderLength(argv[1], argv[2], &argv[3], argc - 3);
	printf("shortest %s->%s: %d\n", argv[1], argv[2], min);
}
