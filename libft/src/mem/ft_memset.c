/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:56:25 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Fills a memory block with a specified byte value.
 *
 * @param ptr (void *) : Pointer to the memory block to fill.
 * @param c (int) : The byte value to set.
 * @param size (size_t) : Number of bytes to set.
 *
 * @return (void *) : Pointer to the memory block filled with the byte value.
 */
void	*ft_memset(void *ptr, int c, size_t size)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)ptr;
	while (size > 0)
	{
		*tmp++ = (unsigned char)c;
		size--;
	}
	return (ptr);
}
