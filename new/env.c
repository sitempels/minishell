/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:59:47 by user              #+#    #+#             */
/*   Updated: 2025/05/21 04:54:49 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Only need to split the value using ft_split with the ':' delimiter

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

	tmp = env_getone(env, "PATH");
	if (!tmp)
		return (NULL);
	path = tmp->value;
	if (!path)
		return (NULL);
	return (path);
}

// Print all env
void	env_print(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

// Unset an env where key = key
int	env_unset(t_env **head, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *head;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*head = tmp->next;
			env_freeone(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

// Add a new env to the list
int	env_export(t_env **head, t_env *new)
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
t_env	*env_getone(t_env *head, char *key)
{
	t_env	*tmp;

	if (!head || !key)
		return (NULL);
	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
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
		if (env_export(&head, env) != 0)
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
