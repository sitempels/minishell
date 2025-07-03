/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:42:34 by user              #+#    #+#             */
/*   Updated: 2025/07/03 04:56:29 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check for valid key (first char must be alpha/_)
static int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	env_print_sorted(t_env *env)
{
	t_env	*sorted;

	sorted = NULL;
	sorted = env_dup(env);
	if (!sorted)
		return ;
	if (env_sortkey(&sorted) != 0)
		return ;
	while (sorted)
	{
		if (sorted->value)
			printf("%s=\"%s\"\n", sorted->key, sorted->value);
		else
			printf("%s\n", sorted->key);
		sorted = sorted->next;
	}
	env_freeall(sorted);
}

// main builtin_export function
// extract_value returns NULL if no '=' in string
int	builtin_export(t_env *env, char **args)
{
	int		i;
	char	*key;
	char	*value;

	if (!args[1])
		return (env_print_sorted(env), 0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			printf("export: `%s': not a valid identifier\n", args[i]);
		else
		{
			key = extract_key(args[i]);
			value = extract_value(args[i]);
			if (!env_getone(env, key, ft_strlen(key)))
				env_addback(&env, new_env(args[i]));
			else if (value)
				env_updateone(&env, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (0);
}
