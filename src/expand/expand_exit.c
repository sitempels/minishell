/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:15:00 by user              #+#    #+#             */
/*   Updated: 2025/07/08 16:04:35 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_code(char *input, int i, int exit_status)
{
	size_t	len;
	char	*res;
	char	*code;

	code = ft_itoa(exit_status);
	if (!code)
		return (input);
	len = ft_strlen(code);
	res = (char *)malloc(sizeof(char) * ft_strlen(input + len + 1));
	if (!res)
		return (free(input), NULL);
	ft_strlcpy(res, input, i);
	ft_strjoin_var(3, res, code, &input[i + 2]);
	free(code);
	free(input);
	return (res);
}
