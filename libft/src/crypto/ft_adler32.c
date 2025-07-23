/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adler32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:32:32 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 05:08:10 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crypto.h"

/**
 * @brief Adler-32 checksum algorithm.
 *
 * @param data (const void *) : The data to calculate the checksum for.
 * @param len (size_t) : The length of the data.
 *
 * @return (unsigned int) : The computed checksum.
 */
unsigned int	ft_adler32(const void *data, size_t len)
{
	unsigned char	*bytes;
	unsigned int	a;
	unsigned int	b;
	size_t			i;

	a = 1;
	b = 0;
	bytes = (unsigned char *)data;
	i = 0;
	while (i < len)
	{
		a = (a + bytes[i]) % 65521;
		b = (b + a) % 65521;
		i++;
	}
	return ((b << 16) | a);
}
