/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:00:47 by user              #+#    #+#             */
/*   Updated: 2025/07/07 17:04:08 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_env_node(char *key, char *value);
static t_env	*init_without_env(void);

t_shell	*init_shell(int mode, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->cli = NULL;
	shell->env = (!envp || !*envp) ? init_without_env() : env_from_envp(envp);
	if (!shell->env)
		return (free(shell), NULL);
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
	char	*new_val;

	if (len == 0)
		len = ft_strlen(key);
	target = env_getone(env, key, len);
	if (!target)
		return (1);
	new_val = ft_itoa(ft_atoi(target->value) + modif);
	if (!new_val)
		return (1);
	free(target->value);
	target->value = new_val;
	return (0);
}

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	if (!key || !value)
		return (free(key), free(value), NULL);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (free(key), free(value), NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

static t_env	*init_without_env(void)
{
	char	*value;
	t_env	*env;
	t_env	*node;

	env = NULL;
	value = malloc(PATH_MAX + 1);
	if (!value)
		return (NULL);
	if (!getcwd(value, PATH_MAX))
	{
		free(value);
		value = ft_strdup("");
		if (!value)
			return (NULL);
	}
	node = create_env_node(ft_strdup("PWD"), value);
	if (!node || env_addback(&env, node) != 0)
		return (env_freeall(env), NULL);
	node = create_env_node(ft_strdup("SHLVL"), ft_strdup("0"));
	if (!node || env_addback(&env, node) != 0)
		return (env_freeall(env), NULL);
	return (env);
}
