/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:06:27 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/10 21:45:18 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Converts an uppercase character to lowercase.
 *
 * @param c (int) : Character to convert.
 *
 * @return (int) : Lowercase equivalent if `c` is uppercase, otherwise `c`.
 */
int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c - 'A' + 'a');
	return (c);
}
