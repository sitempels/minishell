/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mean.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Computes the arithmetic mean of an array of integers.
 *
 * @param arr (int*) : Pointer to the array of integers.
 * @param n (int) : The number of elements in the array.
 *
 * @return (double) : The arithmetic mean, or 0.0 if `n` is 0.
 */
double	ft_mean(int *arr, int n)
{
	int	sum;
	int	i;

	if (n == 0)
		return (0.0);
	i = 0;
	sum = 0;
	while (i < n)
		sum += arr[i++];
	return ((double)sum / n);
}
