/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrnl_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:12:33 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/30 15:16:52 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Prints a string followed by a newline to the specified fd.
 *
 * @param str (char *) : The string to be printed.
 * @param fd (int) : The file descriptor to print the string to.
 *

	* @return (int) : The total number of characters printed.
 */
int	ft_putstrnl_fd(char *str, int fd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str)
		return (len);
	while (str[i])
		len += ft_putchar_fd(str[i++], fd);
	len += ft_putchar_fd('\n', fd);
	return (len);
}
