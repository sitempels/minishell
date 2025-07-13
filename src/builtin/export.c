/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:42:34 by user              #+#    #+#             */
/*   Updated: 2025/07/10 18:13:55 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	env_print_sorted(t_env *env)
{
	t_env	*sorted;
	t_env	*head;

	sorted = env_dup(env);
	if (!sorted)
		return ;
	if (env_sortkey(&sorted) != 0)
	{
		env_freeall(sorted);
		return ;
	}
	head = sorted;
	while (sorted)
	{
		if (sorted->value && sorted->value[0] != '\0')
			printf("declare -x %s=\"%s\"\n", sorted->key, sorted->value);
		else if (sorted->value && sorted->value[0] == '\0')
			printf("declare -x %s=\"\"\n", sorted->key);
		else
			printf("declare -x %s\n", sorted->key);
		sorted = sorted->next;
	}
	env_freeall(head);
}

static t_env	*create_env_no_value(char *key)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(key);
		return (NULL);
	}
	new->key = key;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

static int	handle_new_var(t_env **env, char *arg, char *key)
{
	t_env	*new;

	if (ft_strchr(arg, '='))
	{
		new = new_env(arg);
		if (!new || env_addback(env, new))
		{
			env_freeone(new);
			free(key);
			return (1);
		}
	}
	else
	{
		new = create_env_no_value(key);
		if (!new || env_addback(env, new))
		{
			env_freeone(new);
			return (1);
		}
	}
	return (0);
}

static int	handle_update_var(t_env **env, char *arg, char *key)
{
	char	*value;

	value = extract_value(arg);
	if (!value)
	{
		free(key);
		return (1);
	}
	if (env_updateone(env, key, value))
	{
		free(key);
		free(value);
		return (1);
	}
	free(value);
	free(key);
	return (0);
}

static int	process_export_arg(t_env **env, char *arg, int *error_flag)
{
	char	*key;
	t_env	*existing;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*error_flag = 1;
		return (0);
	}
	key = extract_key(arg);
	if (!key)
		return (1);
	existing = env_getone(*env, key);
	if (!existing)
		return (handle_new_var(env, arg, key));
	else if (ft_strchr(arg, '='))
		return (handle_update_var(env, arg, key));
	free(key);
	return (0);
}

int	builtin_export(t_env **env, char **args)
{
	int	i;
	int	error;
	int	ret;

	error = 0;
	if (!args[1])
	{
		env_print_sorted(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		ret = process_export_arg(env, args[i], &error);
		if (ret)
			return (ret);
		i++;
	}
	return (error);
}
