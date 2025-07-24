/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bkdr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:32:02 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 05:08:10 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crypto.h"

/**
 * @brief BKDR string hash function.
 *
 * @param str (const char *) : The input string to hash.
 *
 * @return (unsigned long) : The resulting hash value.
 */
unsigned long	ft_bkdr(const char *str)
{
	unsigned long	hash;
	int				i;

	hash = 0;
	i = 0;
	while (str[i])
	{
		hash = (hash * 131) + str[i];
		i++;
	}
	return (hash);
}
