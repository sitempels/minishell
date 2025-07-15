/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeforall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:17:16 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:46 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Frees a variable number of pointers.
 *
 * @param num (int) : Number of pointers to be freed.
 *
 * @param ... (void*) : Pointers to be freed.
 */
void	ft_freeforall(int num, ...)
{
	va_list	args;
	void	*ptr;
	int		i;

	va_start(args, num);
	i = 0;
	while (i < num)
	{
		ptr = (void *)va_arg(args, void *);
		if (ptr)
			free(ptr);
		i++;
	}
	va_end(args);
}
