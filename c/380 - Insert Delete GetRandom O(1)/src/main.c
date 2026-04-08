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

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SAFE_CMP(X, Y) ((X > Y) - (X < Y))

#define FS_VEC_INITSIZE 32

#define FS_DECLARE_VEC(T, tag)                                                         \
                                                                                       \
typedef struct Vec_##tag                                                               \
{                                                                                      \
    T		*data;                                                                     \
    size_t	size;                                                                      \
    size_t	capacity;                                                                  \
} Vec_##tag;                                                                           \
                                                                                       \
static inline Vec_##tag *vec_##tag##_init()                                            \
{                                                                                      \
    Vec_##tag *vec = (Vec_##tag *)calloc(1, sizeof(Vec_##tag));                        \
                                                                                       \
	vec->capacity = FS_VEC_INITSIZE;                                                   \
    vec->data = (T *)calloc(FS_VEC_INITSIZE, sizeof(T));                               \
	return vec;                                                                        \
}                                                                                      \
                                                                                       \
static inline void vec_##tag##_push(Vec_##tag *v, T value)                             \
{                                                                                      \
    if (v->size >= v->capacity)                                                        \
	{                                                                                  \
        v->capacity *= 2;                                                              \
        v->data = (T *)realloc(v->data, v->capacity * sizeof(T));                      \
    }                                                                                  \
    v->data[v->size++] = value;                                                        \
}                                                                                      \
                                                                                       \
static inline void vec_##tag##_free(Vec_##tag *v, void (*del)(T))                      \
{                                                                                      \
    if (del != NULL)                                                                   \
	{                                                                                  \
		for (size_t i = 0; i < v->size; i++)                                           \
			del(v->data[i]);                                                           \
	}                                                                                  \
    free(v->data);                                                                     \
	free(v);                                                                           \
}                                                                                      \
                                                                                       \
static inline T vec_##tag##_pop(Vec_##tag *v)                                          \
{                                                                                      \
	return v->data[--v->size];                                                         \
}                                                                                      \


#define FS_DECLARE_HASHMAP(K, V, tag, cmp, hash)                                       \
                                                                                       \
typedef struct HashMap_##tag##_node                                                    \
{                                                                                      \
    K							key;                                                   \
    V							val;                                                   \
	struct HashMap_##tag##_node	*next;                                                 \
} HashMap_##tag##_node;                                                                \
                                                                                       \
typedef struct HashMap_##tag                                                           \
{                                                                                      \
    struct HashMap_##tag##_node	**data;                                                \
    size_t						size;                                                  \
    size_t						capacity;                                              \
} HashMap_##tag;                                                                       \
                                                                                       \
HashMap_##tag##_node	*_hashmap_##tag##_node_new(K key, V val)                       \
{                                                                                      \
	HashMap_##tag##_node *new = calloc(1, sizeof(*new));                               \
	new->key = key;                                                                    \
	new->val = val;                                                                    \
	return new;                                                                        \
}                                                                                      \
                                                                                       \
HashMap_##tag	*hashmap_##tag##_new(size_t size)                                      \
{                                                                                      \
	HashMap_##tag	*new = calloc(1, sizeof(*new));                                    \
	new->data = calloc(size, sizeof(*(new->data)));                                    \
	new->capacity = size;                                                              \
	return new;                                                                        \
}                                                                                      \
                                                                                       \
int hashmap_##tag##_insert(HashMap_##tag *map, K key, V val)                           \
{                                                                                      \
	size_t idx = hash(key) % map->capacity;                                            \
	int (*cmpf)(K, K) = (int (*)(K, K))cmp;                                            \
                                                                                       \
	HashMap_##tag##_node *prev = NULL;                                                 \
	HashMap_##tag##_node *current = map->data[idx];                                    \
	while (current != NULL)                                                            \
	{                                                                                  \
		int diff = (cmpf == NULL)                                                      \
			? SAFE_CMP(key, current->key)                                              \
			: cmpf(key, current->key);                                                 \
		if (diff == 0)                                                                 \
			return 0;                                                                  \
		prev = current;                                                                \
		current = current->next;                                                       \
	}                                                                                  \
	if (prev == NULL)                                                                  \
		map->data[idx] = _hashmap_##tag##_node_new(key, val);                          \
	else                                                                               \
		current->next = _hashmap_##tag##_node_new(key, val);                           \
	map->size++;                                                                       \
	return 1;                                                                          \
}                                                                                      \
                                                                                       \
int hashmap_##tag##_remove(HashMap_##tag *map, K key)                                  \
{                                                                                      \
	size_t idx = hash(key) % map->capacity;                                            \
	int (*cmpf)(K, K) = (int (*)(K, K))cmp;                                            \
                                                                                       \
	HashMap_##tag##_node *prev = NULL;                                                 \
	HashMap_##tag##_node *current = map->data[idx];                                    \
	while (current != NULL)                                                            \
	{                                                                                  \
		int diff = (cmpf == NULL)                                                      \
			? SAFE_CMP(key, current->key)                                              \
			: cmpf(key, current->key);                                                 \
		if (diff == 0)                                                                 \
		{                                                                              \
			if (prev == NULL)                                                          \
				map->data[idx] = current->next;                                        \
			else                                                                       \
				prev->next = current->next;                                            \
			free(current);                                                             \
			map->size--;                                                               \
			return 1;                                                                  \
		}                                                                              \
		prev = current;                                                                \
		current = current->next;                                                       \
	}                                                                                  \
	return 0;                                                                          \
}                                                                                      \
                                                                                       \
V *hashmap_##tag##_get(HashMap_##tag *map, K key)                                      \
{                                                                                      \
	size_t idx = hash(key) % map->capacity;                                            \
                                                                                       \
	HashMap_##tag##_node *current = map->data[idx];                                    \
	int (*cmpf)(K, K) = (int (*)(K, K))cmp;                                            \
	while (current != NULL)                                                            \
	{                                                                                  \
		int diff = (cmpf == NULL)                                                      \
			? SAFE_CMP(key, current->key)                                              \
			: cmpf(key, current->key);                                                 \
		if (diff == 0)                                                                 \
			return &current->val;                                                      \
		current = current->next;                                                       \
	}                                                                                  \
	return NULL;                                                                       \
}                                                                                      \
                                                                                       \
void hashmap_##tag##_delete(HashMap_##tag *map)                                        \
{                                                                                      \
	for (size_t i = 0; i < map->capacity; i++)                                         \
	{                                                                                  \
		HashMap_##tag##_node *current = map->data[i];                                  \
		HashMap_##tag##_node *tmp;                                                     \
		while (current != NULL)                                                        \
		{                                                                              \
			tmp = current->next;                                                       \
			free(current);                                                             \
			current = tmp;                                                             \
		}                                                                              \
	}                                                                                  \
	free(map->data);                                                                   \
	free(map);                                                                         \
}                                                                                      \

size_t hash_int(int num)
{
	return num;
}

FS_DECLARE_VEC(int, int);
FS_DECLARE_HASHMAP(int, size_t, idx, NULL, hash_int);

typedef struct
{
    HashMap_idx	*idxs;
	Vec_int		*vals;
} RandomizedSet;


RandomizedSet* randomizedSetCreate()
{
    RandomizedSet *new = calloc(1, sizeof(*new));
	srand(time(NULL));
	new->idxs = hashmap_idx_new(9999);
	new->vals = vec_int_init();
	return new;
}

bool randomizedSetInsert(RandomizedSet* obj, int val)
{
	int ret;

    if ((ret = hashmap_idx_insert(obj->idxs, val, obj->vals->size)))
		vec_int_push(obj->vals, val);
	return ret;
}

bool randomizedSetRemove(RandomizedSet* obj, int val)
{
	size_t *addr = hashmap_idx_get(obj->idxs, val);
    if (addr == NULL)
		return false;

	size_t idx = *addr;
	obj->vals->data[idx] = vec_int_pop(obj->vals);
	*hashmap_idx_get(obj->idxs, obj->vals->data[idx]) = idx;
	hashmap_idx_remove(obj->idxs, val);
	return true;
}

int randomizedSetGetRandom(RandomizedSet* obj)
{
    return obj->vals->data[rand() % obj->vals->size];
}

void randomizedSetFree(RandomizedSet* obj)
{
	hashmap_idx_delete(obj->idxs);
	vec_int_free(obj->vals, NULL);
}
