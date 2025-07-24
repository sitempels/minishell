/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:12:09 by sjacquet          #+#    #+#             */
/*   Updated: 2025/04/29 06:42:01 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

/**
 * @brief Writes a single character to the specified file descriptor
 *
 * @param c (char) : character to be written
 * @param fd (int) : file descriptor where the character will be written
 *
 * @return (int) : number of bytes written (should be 1)
 */
int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
