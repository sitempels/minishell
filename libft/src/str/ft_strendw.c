/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:16:30 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:24:35 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

/**
 * @brief Checks if `s1` ends with the substring `s2`.
 *
 * @param s1 (char *) : The string to check.
 * @param s2 (char *) : The substring to check against the end of `s1`.
 *
 * @return (int) : 1 if `s1` ends with `s2`, 0 otherwise.
 */
int	ft_strendw(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s2 > len_s1)
		return (0);
	return (ft_strcmp(s1 + len_s1 - len_s2, s2) == 0);
}
