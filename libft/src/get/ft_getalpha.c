/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getalpha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:01:41 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/10 21:27:58 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get.h"

/**
 * @brief Returns a string of alphanumeric characters plus '-' and '_'.
 *
 * @return (char *) : The character set used for random token generation.
 */
const char	*ft_getalpha(void)
{
	return ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_");
}
