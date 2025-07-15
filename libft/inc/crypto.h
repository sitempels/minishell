/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypto.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:15:02 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/10 21:22:53 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRYPTO_H
# define CRYPTO_H

# include "bool.h"
# include "get.h"
# include "libft.h"
# include "mem.h"
# include "str.h"
# include "utils.h"

unsigned int	ft_adler32(const void *data, size_t len);
unsigned int	ft_crc32(const void *data, size_t len);
unsigned int	ft_gcity(const char *key);
unsigned int	ft_murmur(const char *str);

unsigned long	ft_bkdr(const char *str);
unsigned long	ft_djb2(const char *str);
unsigned long	ft_fnv1a(const char *str);
unsigned long	ft_jenkins(const char *str);
unsigned long	ft_sdbm(const char *str);

char			*ft_rot13(char *str);
char			*ft_caesar(char *str, int shift);
char			*ft_vigenere(const char *data, const char *key);
char			*ft_xor(const char *data, const char *key);

#endif
