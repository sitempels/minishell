/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:18:04 by stempels          #+#    #+#             */
/*   Updated: 2025/07/01 14:06:28 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

static char	*append_char(char *s, char c)
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

static char	*append_str(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

static char	*expand_exit_code(char *res, int exit_status)
{
	char	*code;

	code = ft_itoa(exit_status);
	if (!code)
		return (res);
	res = append_str(res, code);
	free(code);
	return (res);
}

static char	*expand_variable(const char *input, size_t *i, t_env *env,
		char *res)
{
	char	*key;
	char	*val;
	size_t	start;

	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	key = ft_strsub(input, start, *i - start);
	if (!key)
		return (res);
	val = get_env_value(env, key);
	free(key);
	if (val)
		res = append_str(res, ft_strdup(val));
	return (res);
}

char	*expand_string(t_shell *shell, const char *input)
{
	size_t	i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '?')
			{
				res = expand_exit_code(res, shell->status);
				i++;
			}
			else if (ft_isalpha(input[i]) || input[i] == '_')
				res = expand_variable(input, &i, shell->env, res);
			else
				res = append_char(res, '$');
		}
		else
		{
			res = append_char(res, input[i]);
			i++;
		}
	}
	return (res);
}

char	*process_arg(t_shell *shell, t_token *arg)
{
	char	*raw;
	char	*expanded;

	raw = (char *)ft_calloc(arg->size + 1, sizeof(char));
	if (!raw)
		return (NULL);
	ft_memcpy(raw, arg->start, arg->size);
	free(arg);
	expanded = expand_string(shell, raw);
	free(raw);
	return (expanded);
}

char	**get_arg(t_shell *shell, t_token *arg, int nbr)
{
	char	**argv;

	if (!arg)
	{
		argv = (char **)ft_calloc(nbr + 1, sizeof(char *));
		if (!argv)
			return (NULL);
		return (argv);
	}
	argv = get_arg(shell, arg->next, nbr + 1);
	if (!argv)
		return (NULL);
	argv[nbr] = process_arg(shell, arg);
	if (!argv[nbr])
		return (NULL);
	argv[nbr] = quote_removal(argv[nbr]);
	return (argv);
}

char	*quote_removal(char *str)
{
	int	i;
	int	j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] == '\'' || str[i + j] == '\"')
		{
			quote = str[i + j++];
			while (str[i + j] && str[i + j] != quote)
			{
				str[i] = str[i + j];
				i++;
			}
			j++;
			continue;
		}
		str[i] = str[i + j];
		i++;
	}
	str = (char *) realloc(str, i);
	str[i] = '\0';
	return (str);
}
