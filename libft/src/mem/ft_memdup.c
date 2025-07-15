/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Duplicates a memory block by allocating new memory and copying
 * the contents.
 *
 * @param ptr (void *) : Pointer to the memory block to duplicate.
 * @param size (size_t) : The size of the memory block to duplicate.
 *
 * @return (void *) : Pointer to the newly allocated memory block containing
 * the duplicated data, or NULL if the allocation fails.
 */
void	*ft_memdup(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = ft_calloc(1, size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	return (new_ptr);
}
