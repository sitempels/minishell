/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:47 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:30:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Capitalizes the first letter of each word in a string,
 * and converts the rest of the letters to lowercase.
 *
 * @param str (char *) : Input string to modify in place.
 *
 * @return (char *) : The modified input string.
 */
char	*ft_strcap(char *str)
{
	int	i;
	int	new_word;

	i = 0;
	new_word = 1;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
		{
			if (new_word && ft_islower(str[i]))
				str[i] = ft_toupper(str[i]);
			else if (!new_word && ft_isupper(str[i]))
				str[i] = ft_tolower(str[i]);
			new_word = 0;
		}
		else if (ft_isdigit(str[i]))
			new_word = 0;
		else
			new_word = 1;
		i++;
	}
	return (str);
}
