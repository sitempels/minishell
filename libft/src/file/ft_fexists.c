/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fexists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:03:10 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 21:36:17 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

/**
 * @brief Checks if a file exists at the specified path.
 *
 * @param path (const char *) : The path of the file to check.
 *
 * @return (int) : 1 if the file exists, 0 if it does not.
 */
int	ft_fexists(const char *path)
{
	if (access(path, F_OK) == 0)
		return (1);
	return (0);
}
