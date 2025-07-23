/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vigenere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:26:33 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 05:08:10 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crypto.h"

/**
 * @brief Encrypts text using the Vigenère cipher.
 *
 * @param data (const char *) : The input string to be encrypted.
 * @param key (const char *) : The encryption key.
 *
 * @return (char *) : The encrypted string.
 */
char	*ft_vigenere(const char *data, const char *key)
{
	char	*result;
	int		dlen;
	int		klen;
	int		i;
	int		k;

	k = 0;
	i = 0;
	dlen = 0;
	while (data[dlen])
		dlen++;
	klen = 0;
	while (key[klen])
		klen++;
	result = (char *)ft_calloc(dlen + 1, sizeof(char));
	if (!result)
		return (0);
	while (i < dlen)
	{
		result[i] = (data[i] + key[k % klen]) % 256;
		i++;
		k++;
	}
	result[i] = 0;
	return (result);
}
