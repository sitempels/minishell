/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:15:02 by kerberos          #+#    #+#             */
/*   Updated: 2025/07/13 09:26:16 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include "bool.h"
# include "libft.h"
# include "mem.h"
# include "num.h"
# include "utils.h"

char	*ft_strcap(char *str);
char	*ft_strchr(const char *str, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s1);
int		ft_strendw(char *s1, char *s2);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strjoin_var(int nbr_of_string, ...);
int		ft_strkcmp(const char *str, const char *key);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);
size_t	ft_strlen(const char *str);
char	*ft_strlower(char *str);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *str1, const char *str2, size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *str, int c);
char	*ft_strrem(char *str, char c);
char	*ft_strrev(char *str);
char	*ft_strrpl(const char *str, const char *old, const char *_new);
char	**ft_strsplit(char const *s, char c);
size_t	ft_strspn(const char *s, char *accept);
int		ft_strstartw(char *s1, char *s2);
char	*ft_strsub(const char *s, unsigned int start, size_t len);
char	*ft_strtok(char *str, const char *delim);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strupper(char *str);
char	*ft_strfmt(const char *fmt, ...);

size_t	ft_stralen(char **arr);
char	**ft_stradup(char **arr);
void	ft_free_array_pos(char ***array, int pos);

#endif
