/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:05:27 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/10 21:45:22 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Converts a lowercase letter to uppercase.
 *
 * @param c (int) : The character to be converted.
 *
 * @return (int) : The uppercase version of `c` if lowercase, else returns `c`.
 */
int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - 'a' + 'A');
	return (c);
}
