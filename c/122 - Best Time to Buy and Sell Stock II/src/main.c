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

int maxProfit(int *prices, int n)
{
	int max = 0;
	int diff;

	for (int i = 1; i < n; i++)
	{
		diff = prices[i] - prices[i - 1];
		max += (diff > 0) ? diff : 0;
	}
	return max;
}

int main(void)
{
	int nums[] = {7,1,5,3,6,4};
	printf("max: %d\n", maxProfit(nums, 6));
}
