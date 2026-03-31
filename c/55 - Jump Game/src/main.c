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
#include <stdbool.h>

bool canJump(int* nums, int n)
{
    n--;
	int prev = n - 1;
	while (n > 0 && prev > -1)
	{
		if (n - prev <= nums[prev])
			n = prev;
		prev--;
	}
	return (n == 0);
}

int main(void)
{
	int nums[] = {2,3,1,1,4};
	int nums2[] = {3,2,1,0,4};

	printf("nums1: %d\nnums2: %d\n", canJump(nums, 5), canJump(nums2, 5));
}



// [3,2,2,0,3,0,0,4]
