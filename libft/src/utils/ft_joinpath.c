/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:01 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:04:26 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Joins two paths together with proper fmtting.
 *
 * @param p1 (char *) : The first path.
 * @param p2 (char *) : The second path.
 *
 * @return (char *) : The combined path or NULL if memory allocation fails.
 */
char	*ft_pathjoin(char *p1, char *p2)
{
	if (!ft_strendw(p1, "/"))
		return (ft_strjoin(p1, ft_strjoin("/", p2)));
	return (ft_strjoin(p1, p2));
}
