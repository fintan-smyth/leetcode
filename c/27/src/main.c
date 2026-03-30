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

int removeElement(int* nums, int numsSize, int val)
{
	for (int i = 0; i < numsSize;)
	{
		if (nums[i] == val)
		{
			int tmp = nums[--numsSize];
			nums[numsSize] = nums[i];
			nums[i] = tmp;
		}
		else
			i++;
	}

	return numsSize;
}
