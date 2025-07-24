/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:15:02 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 04:38:03 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include "libft.h"
# include <stdarg.h>

void	ft_bzero(void *ptr, size_t size);
void	*ft_calloc(size_t count, size_t size);
void	ft_freeforall(int num, ...);
void	*ft_memchr(const void *str, int c, size_t size);
void	*ft_memclear(void *ptr, size_t size);
int		ft_memcmp(const void *str1, const void *str2, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t size);
void	*ft_memdup(void *ptr, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *ptr, int c, size_t size);
void	ft_memswap(void *a, void *b, size_t size);
void	*ft_realloc(void *ptr, unsigned long long old_size,
			unsigned long long new_size);

#endif
