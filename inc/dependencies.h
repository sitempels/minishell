/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dependencies.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:30:18 by user              #+#    #+#             */
/*   Updated: 2025/05/13 01:12:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEPENDENCIES_H
# define DEPENDENCIES_H

/* ************************************************************************** */
/*                                 SYSTEM                                     */
/* ************************************************************************** */

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <termcap.h>
# include <termios.h>
# include <time.h>
# include <unistd.h>

/* ************************************************************************** */
/*                               READLINE                                     */
/* ************************************************************************** */

# include <readline/history.h>
# include <readline/readline.h>

/* ************************************************************************** */
/*                                 CUSTOMS                                    */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                  LIBFT                                     */
/* ************************************************************************** */

# include "../libft/inc/bool.h"
# include "../libft/inc/crypto.h"
# include "../libft/inc/file.h"
# include "../libft/inc/get.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/list.h"
# include "../libft/inc/math.h"
# include "../libft/inc/mem.h"
# include "../libft/inc/num.h"
# include "../libft/inc/put.h"
# include "../libft/inc/str.h"
# include "../libft/inc/utils.h"

#endif /* DEPENDENCIES_H */
