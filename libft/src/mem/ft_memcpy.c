/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:18:08 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Copies `size` bytes from memory area `src` to memory area `dst`.
 *
 * @param dst (void *) : Pointer to the destination memory area.
 * @param src (const void *) : Pointer to the source memory area.
 * @param size (size_t) : The number of bytes to copy.
 *
 * @return (void *) : Pointer to the destination memory area `dst`.
 */
void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == (void *)0 && src == (void *)0)
		return (dst);
	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	while (size > 0)
	{
		*tmp_dst++ = *tmp_src++;
		size--;
	}
	return (dst);
}
