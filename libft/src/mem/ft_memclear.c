/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:56:25 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Clears a block of memory by setting all bytes to zero.
 *
 * @param ptr (void *) : Pointer to the memory block to be cleared.
 * @param size (size_t) : The size of the memory block.
 *
 * @return (void *) : The pointer to the cleared memory block.
 */
void	*ft_memclear(void *ptr, size_t size)
{
	unsigned char	*p;
	size_t			i;

	if (!ptr)
		return (NULL);
	p = (unsigned char *)ptr;
	i = 0;
	while (i < size)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}
