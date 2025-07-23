/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strkcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:03:10 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/30 15:06:17 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Checks if `str` starts with `key` followed by '='.
 *
 * @param str (const char *) : String to compare.
 * @param key (const char *) : Key to check at the start of `str`.
 *
 * @return (int) : 1 if match found, 0 otherwise.
 */
int	ft_strkcmp(const char *str, const char *key)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	if (ft_strncmp(str, key, key_len) == 0 && str[key_len] == '=')
		return (1);
	return (0);
}
