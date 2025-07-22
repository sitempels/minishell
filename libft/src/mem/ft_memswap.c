/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:22 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Swaps the contents of two memory blocks.
 *
 * @param a (void *) : Pointer to the first memory block.
 * @param b (void *) : Pointer to the second memory block.
 * @param size (size_t) : Number of bytes to swap.
 */
void	ft_memswap(void *a, void *b, size_t size)
{
	unsigned char	*ptra;
	unsigned char	*ptrb;
	unsigned char	tmp;
	size_t			i;

	ptra = (unsigned char *)a;
	ptrb = (unsigned char *)b;
	i = 0;
	while (i < size)
	{
		tmp = ptra[i];
		ptra[i] = ptrb[i];
		ptrb[i] = tmp;
		i++;
	}
}
