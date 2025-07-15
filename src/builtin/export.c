/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 07:23:52 by user              #+#    #+#             */
/*   Updated: 2025/07/15 07:25:44 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
