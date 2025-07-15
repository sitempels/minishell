/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:04:52 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/10 21:27:29 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

/**
 * @brief Reads from the file descriptor and stores data in the buffer.
 *
 * @param fd (int) : The file descriptor to read from.
 * @param buffer (char *) : The buffer to store read data.
 *
 * @return (char*) : The updated buffer with the newly read data.
 */
static char	*ft_readfile(int fd, char *buffer)
{
	char	*read_buffer;
	char	*temp;
	ssize_t	bytes_read;

	read_buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(read_buffer), NULL);
		read_buffer[bytes_read] = '\0';
		temp = buffer;
		buffer = ft_strjoin(buffer, read_buffer);
		free(temp);
		if (!buffer)
			return (free(read_buffer), NULL);
	}
	free(read_buffer);
	return (buffer);
}

/**
 * @brief Extracts a line from the buffer up to the newline character.
 *
 * @param buffer (char *) : The buffer to extract the data from a line..
 *
 * @return (char*) : The extracted line.
 */
static char	*ft_getline(char *buffer)
{
	size_t	len;
	char	*line;

	if (!buffer || !*buffer)
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	line = ft_strsub(buffer, 0, len + (buffer[len] == '\n'));
	return (line);
}

/**
 * @brief Trims the buffer, del the part up to and including the first newline.
 *
 * @param buffer (char *) : The buffer to trim.
 *
 * @return (char*) : The remaining part of the buffer after trimming.
 */
static char	*ft_trimbuffer(char *buffer)
{
	char	*new_buffer;
	size_t	len;
	size_t	offset;

	if (!buffer)
		return (NULL);
	len = ft_strlen(buffer);
	offset = 0;
	while (buffer[offset] && buffer[offset] != '\n')
		offset++;
	if (!buffer[offset])
		return (free(buffer), NULL);
	new_buffer = ft_strsub(buffer, offset + 1, len - offset - 1);
	free(buffer);
	return (new_buffer);
}

/**
 * @brief Reads a single line from the file specified by the file descriptor.
 *
 * @param fd (int) : The file descriptor to read from.
 *
 * @return (char*) : A line from the file or NULL if there is no more data.
 */
char	*ft_getnextline(int fd)
{
	static char	*buffer_fd[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!buffer_fd[fd])
		buffer_fd[fd] = ft_calloc(1, sizeof(char));
	buffer_fd[fd] = ft_readfile(fd, buffer_fd[fd]);
	if (!buffer_fd[fd])
		return (NULL);
	line = ft_getline(buffer_fd[fd]);
	buffer_fd[fd] = ft_trimbuffer(buffer_fd[fd]);
	return (line);
}
