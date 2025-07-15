/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crc32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:08:10 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 05:08:10 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crypto.h"

/**
 * @brief Calculates the CRC32 checksum of the input data.
 *
 * @param data (const void *) : The input data to compute the checksum for.
 * @param len (size_t) : The length of the data.
 *
 * @return (unsigned int) : The resulting CRC32 checksum.
 */
unsigned int	ft_crc32(const void *data, size_t len)
{
	const unsigned char	*bytes;
	unsigned int		mask;
	unsigned int		crc;
	unsigned int		i;
	unsigned int		j;

	i = 0;
	crc = 0xFFFFFFFF;
	bytes = (const unsigned char *)data;
	while (i < len)
	{
		crc = crc ^ bytes[i];
		j = 0;
		while (j < 8)
		{
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
			j++;
		}
		i++;
	}
	return (~crc);
}
