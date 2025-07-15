/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:11:39 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 04:37:37 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"

/**
 * @brief Converts a string to an integer in a given base.
 *
 * @param str (const char*) : The string to be converted.
 * @param base (const char*) : The base to convert the string from.
 *
 * @return (int) : The converted integer.
 */
int	ft_atoi_base(const char *str, const char *base)
{
	int	result;
	int	sign;
	int	base_len;
	int	i;

	base_len = ft_strlen(base);
	sign = 1;
	result = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (ft_issign(str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_strchr(base, str[i]))
	{
		result = result * base_len + (ft_strchr(base, str[i]) - base);
		i++;
	}
	return (result * sign);
}
