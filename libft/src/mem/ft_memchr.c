/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:19:51 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Searches for the first occurrence of a byte in a block of memory.
 *
 * @param str (const void *) : Pointer to the memory block to be searched.
 * @param c (int) : The byte value to search for.
 * @param size (size_t) : The size of the memory block.
 *
 * @return (void *) : Pointer to the first occurrence of the byte,
 *                     or NULL if the byte is not found.
 */
void	*ft_memchr(const void *str, int c, size_t size)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	uc;

	ptr = (unsigned char *)str;
	uc = (unsigned char)c;
	i = 0;
	while (i < size)
	{
		if (ptr[i] == uc)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}
