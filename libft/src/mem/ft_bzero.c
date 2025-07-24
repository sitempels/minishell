/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Sets the first `size` bytes of the memory pointed to by `ptr` to zero.
 *
 * @param ptr (void *) : Pointer to the memory area to be set to zero.
 * @param size (size_t) : Number of bytes to set to zero.
 *
 * @return (void) : This function does not return a value.
 */
void	ft_bzero(void *ptr, size_t size)
{
	char	*tmp;

	tmp = (char *)ptr;
	while (size > 0)
	{
		*tmp++ = 0;
		size--;
	}
}
