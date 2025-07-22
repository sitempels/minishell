/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fappend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:03:10 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/10 21:24:04 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

/**
 * @brief Appends a line to the end of a file.
 *
 * @param path (const char *) : Path to the file to append to.
 * @param line (const char *) : The string to append to the file.
 *
 * @return (int) : 0 on success, -1 on failure (file error or write error).
 */
int	ft_fappend(const char *path, char *line)
{
	int	fd;

	fd = open(path, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (-1);
	if (ft_putstr_fd(line, fd) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
