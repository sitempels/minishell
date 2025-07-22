/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:58:30 by user              #+#    #+#             */
/*   Updated: 2025/05/13 00:52:27 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strfmt(const char *fmt, ...)
{
	int		idx;
	va_list	args;
	char	*fmtstr;
	char	*str_arg;

	fmtstr = ft_calloc(1, sizeof(char));
	if (!fmtstr)
		return (NULL);
	va_start(args, fmt);
	idx = 0;
	while (fmt[idx])
	{
		if (fmt[idx] == 's')
		{
			str_arg = va_arg(args, char *);
			ft_strlcat(fmtstr, str_arg, ft_strlen(str_arg) + 1);
		}
		idx++;
	}
	va_end(args);
	return (fmtstr);
}
