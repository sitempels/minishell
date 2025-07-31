/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:42:34 by user              #+#    #+#             */
/*   Updated: 2025/07/31 10:40:45 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_identifier_and_report(char *arg, int *error_flag)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*error_flag = 1;
		return (0);
	}
	return (1);
}

int	is_valid_identifier(const char *str)
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

t_env	*create_env_no_value(char *key)
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

int	handle_new_var(t_env **env, char *arg, char *key)
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
		free(key);
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

int	handle_update_var(t_env **env, char *arg, char *key)
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
