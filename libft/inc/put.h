/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:15:02 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 04:38:33 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_H
# define PUT_H

# include "get.h"
# include "libft.h"

int	ft_printf(const char *fmt, ...);
int	ft_printf_fd(int fd, const char *fmt, ...);

int	ft_putchar(char c);
int	ft_putchar_fd(char c, int fd);
int	ft_putstr(char *str);
int	ft_putstr_fd(char *str, int fd);
int	ft_putstrnl_fd(char *str, int fd);

int	ft_putnbr(long long num);
int	ft_putnbr_fd(int n, int fd);
int	ft_putnbr_base_fd(int n, int base, int fd);

int	ft_puthex(unsigned int n, char fmt);
int	ft_puthex_fd(unsigned int n, char fmt, int fd);

#endif
