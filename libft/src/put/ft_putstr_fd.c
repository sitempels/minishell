/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrfd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:12:22 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/29 06:42:31 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Prints a string to the specified file descriptor.
 *
 * @param str (char *) : The string to be printed.
 * @param fd (int) : The file descriptor where the string will be printed.
 *
 * @return (int) : The total number of characters printed.
 */
int	ft_putstr_fd(char *str, int fd)
{
	int	i;
	int	len;

	if (!str)
		return (ft_putstr_fd("(null)", fd));
	i = 0;
	len = 0;
	while (str[i])
		len += ft_putchar_fd(str[i++], fd);
	return (len);
}
