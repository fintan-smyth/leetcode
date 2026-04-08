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
#include <stdio.h>
#include <stdlib.h>

int *productExceptSelf(int *nums, int n, int *returnSize)
{
    int *answer = malloc(n * sizeof(int));
	*returnSize = n;

	answer[0] = 1;
	for (int i = 1; i < n; i++)
		answer[i] = answer[i - 1] * nums[i - 1];

	int suffix_prod = 1;
	for (int i = n - 1; i >= 0; i--)
	{
		answer[i] *= suffix_prod;
		suffix_prod *= nums[i];
	}

	return answer;
}

int main(void)
{
	int nums[] = {1, 2, 3, 4};
	int nums2[] = {-1, -1, 0, -3, -3};
	int answer_size;
	free(productExceptSelf(nums, 4, &answer_size));
	free(productExceptSelf(nums2, 5, &answer_size));
}
