/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array_pos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 09:23:19 by stempels          #+#    #+#             */
/*   Updated: 2025/07/13 09:37:01 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

void	ft_free_array_pos(char ***array, int pos)
{
	if (!array || !*array)
		return ;
	while ((*array)[pos])
	{
		if ((*array)[pos])
		{
			free((*array)[pos]);
			(*array)[pos] = NULL;
		}
		pos++;
	}
	free(*array);
	*array = NULL;
	return ;
}
