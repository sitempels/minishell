/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvalue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:26:40 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/05 22:04:21 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Returns the index of character `c` in the string `base`.
 *
 * @param c (char) : Character to search for.
 * @param base (const char *) : Base string to search within.
 *
 * @return (int) : Index of `c` in `base`, or -1 if not found.
 */
int	ft_getvalue(char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
		if (c == base[i])
			return (i);
	i++;
	return (-1);
}
