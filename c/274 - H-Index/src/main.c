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

#include <stdio.h>
#include <stdlib.h>

static inline int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int hIndex(int* citations, int n)
{
    qsort(citations, n, sizeof(int), compare);

	int h = 0;
	for (int i = 1; i <= n; i++)
	{
		if (citations[n - i] >= i)
			h = i;
	}
	return h;
}


int main(void)
{
	int nums[] = {2,3,1,1,4};
	int nums2[] = {2,3,0,0,1,4};
	int nums3[] = {5,6,4,4,6,9,4,4,7,4,4,8,2,6,8,1,5,9,6,5,2,7,9,7,9,6,9,4,1,6,8,8,4,4,2,0,3,8,5};

	hIndex(nums3, 39);

	printf("nums1: %d\nnums2: %d\nnums3: %d\n", hIndex(nums, 5), hIndex(nums2, 6), hIndex(nums3, 39));
}


// [2,3,1,0,2,4]
