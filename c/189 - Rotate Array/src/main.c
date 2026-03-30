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

static inline void reverse_arr(int *nums, int start, int end)
{
	int tmp;
	while (--end > start)
	{
		tmp = nums[end];
		nums[end] = nums[start];
		nums[start++] = tmp;
	}
}

// void rotate(int* nums, int n, int k)
// {
// 	k = n - (k % n);
//
// 	reverse_arr(nums, 0, k);
// 	reverse_arr(nums, k, n);
// 	reverse_arr(nums, 0, n);
// }

#include <string.h>

void rotate(int* nums, int n, int k)
{
	k = k % n;
	int copy[n];
	int sub = n - k;

	memcpy(&copy[k], nums, sub * sizeof(int));
	memcpy(copy, &nums[sub], k * sizeof(int));
	memcpy(nums, copy, n * sizeof(int));
}
