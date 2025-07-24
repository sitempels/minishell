/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gethex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:23:10 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/10 21:28:25 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get.h"

/**
 * @brief Returns a string of hexadecimal characters based on the fmt.
 *
 * @param fmt (char) : 'X' for uppercase hex, any other value for lowercase.
 *
 * @return (char *) : The hexadecimal character set.
 */
const char	*ft_gethex(const char format)
{
	if (format == 'X')
		return ("0123456789ABCDEF");
	return ("0123456789abcdef");
}
