/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:01 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/10 21:45:10 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Processes input from a file descriptor to skip spaces and sign chars.
 *
 * @param fd (int) : File descriptor to read from.
 * @param base (const char *) : Base characters (not used in function).
 * @param sign (int *) : Pointer to store detected sign (-1 or 1).
 *
 * @return (int) : First non-space, non-sign character read (as int),
 *                 or 0 on read failure or EOF.
 */
int	ft_process_fd(int fd, const char *base, int *sign)
{
	char	buffer[2];
	int		read_bytes;

	read_bytes = read(fd, buffer, 1);
	if (read_bytes <= 0)
		return (0);
	if (ft_isspace(buffer[0]))
		return (ft_process_fd(fd, base, sign));
	if (buffer[0] == '-' || buffer[0] == '+')
	{
		if (buffer[0] == '-')
			*sign = -1;
		else
			*sign = 1;
		return (ft_process_fd(fd, base, sign));
	}
	return (buffer[0]);
}
