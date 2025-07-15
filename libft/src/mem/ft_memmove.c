/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:01 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Copies a memory block from source to destination, handling overlapping
 * regions correctly.
 *
 * @param dst (void *) : Pointer to the destination memory block.
 * @param src (const void *) : Pointer to the source memory block.
 * @param len (size_t) : Number of bytes to copy.
 *
 * @return (void *) : Pointer to the destination memory block, or NULL if either
 * the destination or source is NULL.
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*c_dst;
	const unsigned char	*c_src;

	if (!dst && !src)
		return (NULL);
	c_dst = (unsigned char *)dst;
	c_src = (const unsigned char *)src;
	if (c_dst > c_src)
		while (len--)
			c_dst[len] = c_src[len];
	else
		while (len--)
			*c_dst++ = *c_src++;
	return (dst);
}
