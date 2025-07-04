/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:15:00 by user              #+#    #+#             */
/*   Updated: 2025/07/04 09:34:40 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_code(char *res, int exit_status)
{
	char	*code;

	code = ft_itoa(exit_status);
	if (!code)
		return (res);
	res = append_str(res, code);
	free(code);
	return (res);
}
