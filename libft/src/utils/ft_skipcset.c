/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipcset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:09:25 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:32:05 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Skips over any delimiters in the string `str`.
 *
 * @param str (char *) : The string to be processed.
 * @param delim (const char *) : The string containing delimiters.
 *
 * @return (char *) : The pointer to the first non-delimiter character in `str`.
 */
char	*ft_skipcset(char *str, const char *cset)
{
	while (*str && ft_strchr(cset, *str))
		str++;
	return (str);
}
