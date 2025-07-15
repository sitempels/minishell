/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:01:45 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Allocate memory for `count` elem of `size` bytes, init all to zeroes.
 *
 * @param count (size_t) : Number of elements.
 * @param size (size_t) : Size of each element.
 *
 * @return (void *) : Pointer to allocated memory, or NULL on failure.
 */
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = (unsigned char *)malloc(count * size);
	if (!tmp)
		return (NULL);
	while (i < count * size)
		tmp[i++] = 0;
	return (tmp);
}
