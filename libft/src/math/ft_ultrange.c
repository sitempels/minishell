/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultrange.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:07:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

/*
 * @brief Creates an array of integers from `min` to `max
 *- 1` and assigns it to a pointer.
 *
 * @param range (int **) : A pointer to the array.
 * @param min (int) : The starting value.
 * @param max (int) : The ending value (exclusive).
 *
 * @return (int) : The number of elements, or 0 if `min` >= `max`.
 */
int	ft_math_ultrange(int **range, int min, int max)
{
	int	i;
	int	*tab;

	i = 0;
	tab = 0;
	if (min >= max)
	{
		*range = 0;
		return (0);
	}
	tab = (int *)malloc(sizeof(*tab) * (max - min + 1));
	while (min < max)
	{
		tab[i] = min;
		min++;
		i++;
	}
	tab[i] = '\0';
	*range = tab;
	return (i);
}
