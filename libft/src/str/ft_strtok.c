/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:09:25 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/30 15:06:17 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Tokenizes a string based on a set of delimiters.
 *
 * @param str (char *) : The string to be tokenized. If NULL,
 * continues tokenizing previous string from where it was left off.
 * @param delim (const char *) : A string containing all delimiter characters.
 *
 * @return (char *) : A pointer to the next token, or NULL if no more tokens.
 */
char	*ft_strtok(char *str, const char *delim)
{
	static char	*saved_str = NULL;
	char		*token;

	if (str)
		saved_str = str;
	if (!saved_str)
		return (NULL);
	saved_str = ft_skipcset(saved_str, delim);
	if (*saved_str == '\0')
	{
		saved_str = NULL;
		return (NULL);
	}
	token = saved_str;
	while (*saved_str && !ft_strchr(delim, *saved_str))
		saved_str++;
	if (*saved_str != '\0')
	{
		*saved_str = '\0';
		saved_str++;
	}
	return (token);
}
