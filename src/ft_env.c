/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:51:26 by user              #+#    #+#             */
/*   Updated: 2025/05/11 19:17:02 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_keymatch(char *curr, const char *key)
{
	char	*eq;
	size_t	len;

	eq = ft_strchr(curr, '=');
	if (eq != NULL)
	{
		len = eq - curr;
		if (ft_strncmp(curr, key, len) == 0 && len == ft_strlen(key))
			return (SUCCESS);
	}
	return (FAILURE);
}

static int	ft_add(char ***arr, const char *new_elem)
{
	int		count;
	char	**new_arr;

	count = ft_count(*arr);
	new_arr = malloc(sizeof(char *) * (count + 2));
	if (!new_arr)
		return (FAILURE);
	count = 0;
	while ((*arr)[count])
	{
		new_arr[count] = ft_strdup((*arr)[count]);
		count++;
	}
	new_arr[count] = ft_strdup(new_elem);
	if (!new_arr[count])
	{
		free(new_arr);
		return (FAILURE);
	}
	new_arr[count + 1] = NULL;
	ft_free(*arr);
	*arr = new_arr;
	return (SUCCESS);
}

static int	ft_update(char **arr, const char *key, const char *value)
{
	int		count;
	char	*tmp;

	count = 0;
	while (arr[count])
	{
		if (ft_keymatch(arr[count], key))
		{
			free(arr[count]);
			tmp = ft_strjoin(key, "=");
			if (!tmp)
				return (FAILURE);
			arr[count] = ft_strjoin(tmp, value);
			free(tmp);
			if (!arr[count])
				return (FAILURE);
			return (SUCCESS);
		}
		count++;
	}
	return (ft_add(&arr, ft_strjoin(key, "=")));
}

static int	ft_remove(char **arr, const char *key)
{
	int	count;
	int	find;

	count = 0;
	find = 0;
	while (arr[count])
	{
		if (ft_match_key(arr[count], key))
		{
			free(arr[count]);
			find = 1;
		}
		if (find && arr[count + 1] != NULL)
			arr[count] = arr[count + 1];
		count++;
	}
	if (find)
	{
		arr[count - 1] = NULL;
		return (SUCCESS);
	}
	return (FAILURE);
}

static int	ft_cmparr(const void *a, const void *b)
{
	return (ft_strcmp(*(const char **)a, *(const char **)b));
}

static int	ft_swap(void *a, void *b, size_t size)
{
	unsigned char	*byte_a;
	unsigned char	*byte_b;
	unsigned char	tmp;

	byte_a = (unsigned char *)a;
	byte_b = (unsigned char *)b;
	while (size--)
	{
		tmp = *byte_a;
		*byte_a = *byte_b;
		*byte_b = tmp;
		byte_a++;
		byte_b++;
	}
	return (SUCCESS);
}

static size_t	ft_partition(char **arr, size_t left, size_t right,
		comparison_fn_t fncmp)
{
	char	*pivot;

	pivot = arr[(left + right) / 2];
	while (left <= right)
	{
		while (fncmp(arr[left], pivot) < 0)
			left++;
		while (fncmp(arr[right], pivot) > 0)
			right--;
		if (left <= right)
		{
			ft_swap(&arr[left], &arr[right], sizeof(char *));
			left++;
			right--;
		}
	}
	return (left);
}

static int	ft_straqsort(char **arr, size_t left, size_t right,
		comparison_fn_t fncmp)
{
	size_t	partition_index;

	if (left >= right)
		return (SUCCESS);
	partition_index = ft_partition(arr, left, right, fncmp);
	if (ft_straqsort(arr, left, partition_index - 1, fncmp) == FAILURE)
		return (FAILURE);
	if (ft_straqsort(arr, partition_index, right, fncmp) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
