/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_caesar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:17:16 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 05:08:10 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crypto.h"

/**
 * @brief Applies the Caesar cipher to a string.
 *
 * @param str (char *) : The input string to be encoded.
 * @param shift (int) : The number of positions to shift each letter.
 *
 * @return (char *) : The encoded string.
 */
char	*ft_caesar(char *str, int shift)
{
	int	i;

	i = 0;
	shift %= 26;
	while (str[i])
	{
		if (ft_isupper(str[i]))
		{
			str[i] = ((str[i] - 'A' + shift) % 26) + 'A';
		}
		else if (ft_islower(str[i]))
		{
			str[i] = ((str[i] - 'a' + shift) % 26) + 'a';
		}
		i++;
	}
	return (str);
}
