/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:15:02 by kerberos          #+#    #+#             */
/*   Updated: 2025/06/05 16:41:58 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "const.h"
# include "libft.h"
# include "mem.h"
# include "put.h"
# include "str.h"

int		ft_fappend(const char *path, char *line);
int		ft_fcopy(const char *spath, const char *dpath);
int		ft_fcountline(const char *path);
int		ft_fcreate(const char *path, char *line);
int		ft_fexists(const char *path);
char	*ft_getnextline(int fd);

#endif
