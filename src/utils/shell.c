/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:00:47 by user              #+#    #+#             */
/*   Updated: 2025/07/07 11:08:15 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_env_node(char *key, char *value);
static t_env	*init_without_env(void);

t_shell	*init_shell(int mode, char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->cli = NULL;
	if (!envp || !*envp)
		shell->env = init_without_env();
	else
		shell->env = env_from_envp(envp);
	if (!shell->env)
	{
		free(shell);
		return (NULL);
	}
	shell->tokens = NULL;
	shell->tree = NULL;
	shell->mode = mode;
	shell->status = 0;
	shell->child_nbr = 0;
	shell->std_io[0] = ttyname(STDOUT_FILENO);
	shell->std_io[1] = ttyname(STDIN_FILENO);
	if (update_envint(shell->env, "SHLVL", 0, 1))
		ft_error(shell, 0, 1, "LOST IS SHELL LVL");
	return (shell);
}

int	update_envint(t_env *env, char *key, size_t len, int modif)
{
	t_env	*target;

	if (len == 0)
		len = ft_strlen(key);
	target = env_getone(env, key, len);
	if (!target)
		return (1);
	target->value = ft_itoa(ft_atoi(target->value) + modif);
	return (0);
}

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	return (new);
}

static t_env	*init_without_env(void)
{
	char	*value;
	t_env	*new;
	t_env	*env;

	env = NULL;
	value = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
	if (!value)
		return (NULL);
	if (getcwd(value, PATH_MAX) == NULL)
	{
		free(value);
		value = ft_strdup("");
		if (!value)
			return (NULL);
	}
	new = create_env_node(ft_strdup("PWD"), value);
	if (!new)
	{
		free(value);
		return (NULL);
	}
	env_addback(&env, new);
	env_addback(&env, create_env_node(ft_strdup("SHLVL"), ft_strdup("0")));
	return (env);
}

// static t_env	*init_without_env(void)
// {
// 	char	*value;
// 	t_env	*new;
// 	t_env	*env;

// 	value = (char *)malloc(sizeof(char) * (42 + 1));
// 	new = create_env_node("PWD", getcwd(value, sizeof(value)));
// 	env_addback(&env, new);
// 	env_addback(&env, create_env_node("SHLVL", "0"));
// 	return (env);
// }
