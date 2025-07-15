/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fcreate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:03:10 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:17 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

/**
 * @brief Creates a file and writes a line to it, trunc if it already exists.
 *
 * @param path (const char *) : The path to the file to create or truncate.
 * @param line (char *) : The content to write to the file.
 *
 * @return (int) : 0 on success, -1 on error.
 */

int	ft_fcreate(const char *path, char *line)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	if (write(fd, line, ft_strlen(line)) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
