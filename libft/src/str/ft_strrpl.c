/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrpl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:11:27 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/30 15:06:17 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Replaces the first occurrence of `old` with `new` in `str`.
 *
 * @param str (const char *) : String to modify.
 * @param old (const char *) : Substring to replace.
 * @param new (const char *) : Substring to replace with.
 *
 * @return (char *) : New string with replacement or duplicate if no match.
 */
char	*ft_strrpl(const char *str, const char *old, const char *_new)
{
	size_t	old_len;
	size_t	new_len;
	size_t	rest_len;
	char	*result;

	old_len = ft_strlen(old);
	new_len = ft_strlen(_new);
	if (ft_strncmp(str, old, old_len) != 0)
		return (NULL);
	rest_len = ft_strlen(str) - old_len;
	result = (char *)ft_calloc(1, new_len + rest_len + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, _new);
	ft_strcpy(result + new_len, str + old_len);
	return (result);
}
