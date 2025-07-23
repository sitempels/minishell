/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:15:02 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 04:38:56 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "str.h"

int		ft_baselen(unsigned long nbr, int base_len);
int		ft_getvalue(char c, const char *base);
char	*ft_pathjoin(char *p1, char *p2);
int		ft_process_fd(int fd, const char *base, int *sign);
char	*ft_skipcset(char *str, const char *cset);
int		ft_tolower(int c);
int		ft_toupper(int c);

#endif
