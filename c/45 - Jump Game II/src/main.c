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

// int jump_r(int *nums, int idx, int n)
// {
// 	int jump = nums[idx];
// 	if (idx + jump >= n - 1)
// 		return 1;
//
// 	int min = INT_MAX;
// 	while (jump > 0)
// 	{
// 		int n_jumps = jump_r(nums, idx + jump, n);
// 		if (n_jumps < min)
// 			min = n_jumps;
// 		jump--;
// 	}
// 	return (min == INT_MAX ? min : min + 1);
// }

int jump(int* nums, int n)
{
	int jumps = 0;
	int end = 0;
	int farthest = 0;

	for (int i = 0; i < n - 1; i++)
	{
		farthest = (farthest >= i + nums[i]) ? farthest : i + nums[i];

		if (farthest >= n - 1)
		{
			jumps++;
			break;
		}

		if (i == end)
		{
			jumps++;
			end = farthest;
		}
	}

	return jumps;
}

int main(void)
{
	int nums[] = {2,3,1,1,4};
	int nums2[] = {2,3,0,0,1,4};
	int nums3[] = {5,6,4,4,6,9,4,4,7,4,4,8,2,6,8,1,5,9,6,5,2,7,9,7,9,6,9,4,1,6,8,8,4,4,2,0,3,8,5};

	printf("nums1: %d\nnums2: %d\nnums3: %d\n", jump(nums, 5), jump(nums2, 6), jump(nums3, 39));
}


// [2,3,1,0,2,4]
