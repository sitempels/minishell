/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:23:28 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Compares two memory blocks byte by byte.
 *
 * @param str1 (const void *) : Pointer to the first memory block.
 * @param str2 (const void *) : Pointer to the second memory block.
 * @param size (size_t) : The number of bytes to compare.
 *
 * @return (int) : 0 if the blocks are identical, a positive or negative value
 * if the blocks are different, based on the first differing byte.
 */
int	ft_memcmp(const void *str1, const void *str2, size_t size)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	ptr1 = (const unsigned char *)str1;
	ptr2 = (const unsigned char *)str2;
	i = 0;
	if (size == 0)
		return (0);
	while (i < size)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
