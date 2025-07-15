/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/10 21:29:52 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Resizes a previously allocated memory block to a new size.
 *
 * @param ptr (void *) : Pointer to the previously allocated memory block.
 * @param old_size (unsigned long long) : Previous size of the memory block.
 * @param new_size (unsigned long long) : New size for the memory block.
 *
 * @return (void *) : Pointer to the newly allocated memory block,
 * or NULL if the reallocation fails.
 */
void	*ft_realloc(void *ptr, unsigned long long old_size,
		unsigned long long new_size)
{
	char				*new_ptr;
	unsigned long long	i;

	i = 0;
	new_ptr = ft_calloc(new_size, sizeof(char));
	while (i < old_size)
	{
		new_ptr[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}
