/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:52:38 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 05:08:10 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crypto.h"

/**
 * @brief Encrypts a string using XOR encryption with a repeating key.
 *
 * @param data (const char *) : The input string to be encrypted.
 * @param key (const char *) : The key used for XOR encryption.
 *
 * @return (char *) : The resulting encrypted string.
 */
char	*ft_xor(const char *data, const char *key)
{
	const char	*input;
	char		*result;
	size_t		data_len;
	size_t		key_len;
	size_t		index;

	index = 0;
	data_len = ft_strlen(data);
	key_len = ft_strlen(key);
	result = (char *)ft_calloc((data_len + 1), sizeof(char));
	if (!result)
		return (NULL);
	input = data;
	while (index < data_len)
	{
		result[index] = input[index] ^ key[index % key_len];
		index++;
	}
	result[data_len] = '\0';
	return (result);
}
