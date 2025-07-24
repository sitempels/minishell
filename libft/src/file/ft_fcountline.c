/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fcountline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:03:10 by sjacquet          #+#    #+#             */
/*   Updated: 2025/06/05 16:42:07 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

/**
 * @brief Counts the number of newline-separated lines in a file.
 *
 * @param path (const char *) : The path to the file to read.
 *
 * @return (int) : The number of lines in the file, or -1 on error.
 */
int	ft_fcountline(const char *path)
{
	int		fd;
	int		count;
	int		bytes_read;
	char	buffer[BUFFER_SIZE];
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	count = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
				count++;
			i++;
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	close(fd);
	return (count);
}
