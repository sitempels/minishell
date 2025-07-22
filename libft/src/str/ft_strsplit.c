/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:05:51 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/30 15:06:17 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Counts words in a string separated by `sep`.
 *
 * @param s (const char *) : String to scan.
 * @param sep (char) : Separator character.
 *
 * @return (size_t) : Number of words.
 */

static size_t	word_count(const char *s, char sep)
{
	size_t		count;
	const char	*str;

	if (!s)
		return (0);
	count = 0;
	str = s;
	while (*str)
	{
		while (*str && (*str == sep))
			str++;
		if (*str)
			count++;
		while (*str && !(*str == sep))
			str++;
	}
	return (count);
}

/**
 * @brief Returns the length of the next word in `s`.
 *
 * @param s (const char *) : String to scan.
 * @param sep (char) : Separator character.
 *
 * @return (size_t) : Length of the word.
 */
static size_t	word_len(const char *s, char sep)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] && !(s[len] == sep))
		len++;
	return (len);
}

/**
 * @brief Allocates and copies a word from `s`.
 *
 * @param s (const char *) : Source string.
 * @param sep (char) : Separator character.
 *
 * @return (char *) : New string with the word, or NULL if allocation fails.
 */
static char	*fill_word(const char *s, char sep)
{
	size_t	len;
	char	*word;
	char	*unoffset_word;

	len = word_len(s, sep);
	word = (char *)ft_calloc((len + 1), sizeof(char));
	if (!word)
		return (NULL);
	unoffset_word = word;
	while (len-- > 0)
		*(word++) = *(s++);
	return ((char *)unoffset_word);
}

static char	**ft_memfree_split(char **tab)
{
	char	**unoffset_tab;

	unoffset_tab = tab;
	while (*unoffset_tab)
		free(*unoffset_tab++);
	free(tab);
	return (NULL);
}

/**
 * @brief Splits `s` into an array of strings separated by `c`.
 *
 * @param s (char const *) : String to split.
 * @param c (char) : Separator character.
 *
 * @return (char **) : Array of strings, NULL on error.
 */
char	**ft_strsplit(char const *s, char c)
{
	char	**tab;
	char	**unoffset_tab;

	if (!s)
		return (NULL);
	tab = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	unoffset_tab = tab;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			*tab = fill_word(s, c);
			if (!*tab)
				return (ft_memfree_split(unoffset_tab));
			tab++;
		}
		while (*s && !(*s == c))
			s++;
	}
	*tab = NULL;
	return (unoffset_tab);
}
