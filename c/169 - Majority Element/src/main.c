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

int majorityElement(int *nums, int n)
{
    int candidate;
	int count = 0;

	for (int i = 0; i < n; i++)
	{
		if (count == 0)
			candidate = nums[i];
		count += (nums[i] == candidate) ? 1 : -1;
	}
	return candidate;
}
