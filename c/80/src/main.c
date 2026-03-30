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

int removeDuplicates(int* nums, int numsSize)
{
	int k = 0;
	int	dup = 0;
	for (int i = 1; i < numsSize; i++)
	{
		if (nums[i] > nums[k])
		{
			nums[++k] = nums[i];
			dup = 0;
		}
		else if (nums[i] == nums[k] && !dup)
		{
			nums[++k] = nums[i];
			dup = 1;
		}
	}
	return k + 1;
}

//  v
// 000112233345668999
// ^
// 0
//
// 00112233456689
