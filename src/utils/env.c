/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:59:47 by user              #+#    #+#             */
/*   Updated: 2025/06/13 05:42:40 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Update the value of an environment variable in the env list.
int	env_updateone(t_env **head, char *key, char *value)
{
	t_env	*tmp;

	if (!head || !*head || !key || !value)
		return (1);
	tmp = env_getone(*head, key, ft_strlen(key));
	if (!tmp)
		return (1);
	free(tmp->value);
	tmp->value = ft_strdup(value);
	if (!tmp->value)
		return (1);
	return (0);
}

// Return the complete env value as a string "KEY=VALUE"
char	*envp_getone(t_env *env)
{
	char	*result;

	if (!env || !env->key || !env->value)
		return (NULL);
	result = ft_strjoin(env->key, "=");
	if (!result)
		return (NULL);
	result = ft_strjoin(result, env->value);
	return (result);
}

// Return the complete env as an array of strings "KEY=VALUE"
char	**envp_from_env(t_env *env)
{
	char	**result;
	t_env	*tmp;
	size_t	i;

	if (!env)
		return (NULL);
	result = ft_calloc(env_size(env) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		result[i] = envp_getone(tmp);
		if (!result[i])
		{
			free(result);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	return (result);
}

// Get all the paths in an array of string
char	**env_getallpaths(char *path)
{
	char	**paths;

	paths = ft_strsplit(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

// Get all the paths in one string "path"
char	*env_getpath(t_env *env)
{
	char	*path;
	t_env	*tmp;

	tmp = env_getone(env, "PATH", 4);
	if (!tmp)
		return (NULL);
	path = tmp->value;
	if (!path)
		return (NULL);
	return (path);
}

// Extract the key from an env string
char	*extract_key(char *env)
{
	char	*key;
	size_t	len;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	key = ft_calloc(len + 1, sizeof(char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, env, len + 1);
	return (key);
}

// Extract the value from an env string
char	*extract_value(char *env)
{
	char	*value;
	size_t	start;
	size_t	len;

	start = 0;
	while (env[start] && env[start] != '=')
		start++;
	if (!env[start])
		return (NULL);
	start++;
	len = 0;
	while (env[start + len])
		len++;
	value = ft_calloc(len + 1, sizeof(char));
	if (!value)
		return (NULL);
	ft_strlcpy(value, &env[start], len + 1);
	return (value);
}

// Create a new new env node by extracting the key=value
t_env	*new_env(char *env)
{
	t_env	*new;
	char	*key;
	char	*value;

	if (!ft_strchr(env, '='))
		return (NULL);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	key = extract_key(env);
	if (!key)
		return (free(new), NULL);
	value = extract_value(env);
	if (!value)
		return (free(key), free(new), NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

// Get the last node of the env list
t_env	*env_getlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// Add one env node to the front of the env list
int	env_addfront(t_env **head, t_env *new)
{
	if (!head || !new)
		return (1);
	new->next = *head;
	*head = new;
	return (0);
}

// Get one node from the list where key = key
t_env	*env_getone(t_env *head, char *key, size_t len)
{
	t_env	*tmp;

	if (!head || !key)
		return (NULL);
	tmp = head;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, len) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	env_addback(t_env **head, t_env *new)
{
	t_env	*last;

	if (!new)
		return (1);
	if (!*head)
	{
		*head = new;
		return (0);
	}
	last = env_getlast(*head);
	last->next = new;
	return (0);
}

// get one, free one
int	env_delone(t_env **head, char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!head || !*head || !key)
		return (1);
	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			env_freeone(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}

// Get the size of envp
int	envp_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

// Create the env list from envp
t_env	*env_from_envp(char **envp)
{
	t_env	*head;
	t_env	*env;
	size_t	size;
	size_t	i;

	i = 0;
	head = NULL;
	size = envp_size(envp);
	while (i < size)
	{
		env = new_env(envp[i]);
		if (!env)
		{
			env_freeall(head);
			return (NULL);
		}
		if (env_addback(&head, env) != 0)
		{
			env_freeall(head);
			env_freeone(env);
			return (NULL);
		}
		i++;
	}
	return (head);
}

// Free one node of the env list
void	env_freeone(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

// Free all nodes from the env list
void	env_freeall(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		env_freeone(env);
		env = tmp;
	}
}

// Return the size of the env list (nbr of nodes)
size_t	env_size(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
		env = env->next, i++;
	return (i);
}
// sorting
t_env	*env_dup(t_env *src)
{
	t_env	*copy;
	t_env	*new;

	copy = NULL;
	while (src)
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			return (env_freeall(copy), NULL);
		new->key = ft_strdup(src->key);
		new->value = src->value ? ft_strdup(src->value) : NULL;
		if (!new->key || (src->value && !new->value))
			return (env_freeall(copy), env_freeone(new), NULL);
		env_addback(&copy, new);
		src = src->next;
	}
	return (copy);
}

static void	env_swap_content(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

int	env_sortkey(t_env **head)
{
	t_env	*i;
	t_env	*j;
	t_env	*copy;

	if (!head || !*head)
		return (1);
	copy = env_dup(*head);
	if (!copy)
		return (1);
	i = copy;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0)
				env_swap_content(i, j);
			j = j->next;
		}
		i = i->next;
	}
	env_freeall(*head);
	*head = copy;
	return (0);
}
