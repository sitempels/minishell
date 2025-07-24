/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jenkins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:17:16 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 05:08:10 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crypto.h"

/**
 * @brief Implements the Jenkins One-at-a-Time hash function.
 *
 * @param str (const char*) : The null-terminated string to hash.
 *
 * @return (unsigned long) : The computed hash value for the string.
 */
unsigned long	ft_jenkins(const char *str)
{
	unsigned long	hash;
	int				c;

	hash = 0;
	while (*str)
	{
		c = *str++;
		hash += c;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return (hash);
}
