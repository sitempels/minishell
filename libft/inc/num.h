/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:15:02 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/12 23:31:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUM_H
# define NUM_H

# include "bool.h"
# include "libft.h"
# include "mem.h"
# include "str.h"

int				ft_atoi_base(const char *str, const char *base);
int				ft_atoi(const char *str);
long			ft_atol(const char *str);
unsigned long	ft_atoul(const char *str);
char			*ft_uitoa(unsigned int n);
char			*ft_itoa_base(unsigned int n, const char *base);
char			*ft_itoa(int n);
char			*ft_ultoa(unsigned long n);
char			*ft_utoa(unsigned int n);
int				ft_numlen(int num, int base);
int				ft_isintflow(long result, int sign);
long			ft_checkover_underflow(long result, int sign);

#endif
