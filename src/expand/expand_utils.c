/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:10:00 by user              #+#    #+#             */
/*   Updated: 2025/07/26 17:44:50 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_full_path(char **paths, char *cmd, int mode);

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*append_char(char *s, char c)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s, len + 1);
	new[len] = c;
	new[len + 1] = '\0';
	free(s);
	return (new);
}

char	*get_path(t_shell *shell, char *cmd, t_env *env, int mode)
{
	int		error;
	char	*path_full;
	char	**paths;
	t_env	*target;

	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (ft_error(shell, 0, 3, cmd, ": ", get_errnum(C_MISS)), NULL);
	error = access(cmd, mode);
	if (error == 0)
		return (cmd);
	target = env_getone(env, "PATH");
	if (!target || !target->value[0])
		return (ft_error(shell, 0, 3, cmd, ": ", get_errnum(N_SUCH)), NULL);
	paths = ft_strsplit((env_getone(env, "PATH"))->value, ':');
	if (!paths)
		return (NULL);
	path_full = get_full_path(paths, cmd, mode);
	if (!path_full)
		ft_error(shell, 0, 3, cmd, ": ", get_errnum(C_MISS));
	return (ft_free_array_pos(&paths, 0), path_full);
}

static char	*get_full_path(char **paths, char *cmd, int mode)
{
	int		i;
	int		error;
	char	*path_full;

	i = 0;
	path_full = NULL;
	while (paths[i])
	{
		path_full = ft_strjoin_var(3, paths[i], "/", cmd);
		error = access(path_full, mode);
		if (error == 0)
			break ;
		free(path_full);
		path_full = NULL;
		i++;
	}
	return (path_full);
}
