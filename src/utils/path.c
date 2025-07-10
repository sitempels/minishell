/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:52:04 by stempels          #+#    #+#             */
/*   Updated: 2025/07/10 18:14:46 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	**get_all_paths(char *name, char **env);
// static char	*get_full_path(char const *s1, char const *s2);

char	*get_path(char *cmd, t_env *env, int mode)
{
	int		i;
	int		error;
	char	*path_full;
	char	**paths;

	paths = ft_strsplit((env_getone(env, "PATH"))->value, ':');
	if (!paths)
		return (NULL);
	error = access(cmd, mode);
	if (error == 0)
		return (cmd);
	i = 0;
	while (paths[i])
	{
		path_full = ft_strjoin_var(3, paths[i], "/", cmd);
		error = access(path_full, mode);
		if (error == 0)
			return (free_array(paths, 0), free(paths), path_full);
		free(path_full);
		path_full = NULL;
		i++;
	}
	free_array(paths, 0);
	free(paths);
	return (NULL);
}
/*
int	is_builtin(char *cmd, char *path)
{
	return (0);
}
*/
/*static char	**get_all_paths(char *name, char **env)
{
	int		i;
	char	**paths;
	size_t	n_size;
	char	*s3;
	size_t	lens1;
	size_t	lens2;
	size_t	i;
	size_t	j;

	n_size = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_memcmp(env[i], name, n_size) == 0)
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	paths = ft_strsplit(&env[i][n_size + 1], ':');
	return (paths);
}*/
/*
static char	*get_full_path(char const *s1, char const *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (lens1 + lens2 + 2));
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		s3[j++] = s1[i++];
	s3[j++] = '/';
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j] = 0;
	return (s3);
}
*/
