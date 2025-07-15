/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/**
 * @brief Creates an array of integers from `min` to `max - 1`.
 *
 * @param min (int) : Starting value of the range.
 * @param max (int) : Ending value of the range (exclusive).
 *
 * @return (int *) : Pointer to the array, or NULL if `min >= max`.
 */
int	*ft_range(int min, int max)
{
	int	*range;
	int	i;

	i = 0;
	if (min >= max)
		return (0);
	range = (int *)malloc(sizeof(int) * (max - min + 1));
	while (min < max)
	{
		range[i] = min;
		min++;
		i++;
	}
	range[i] = '\0';
	return (range);
}
