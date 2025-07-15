/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:15:02 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/11 04:38:19 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "libft.h"
# include "mem.h"

typedef struct s_list_node
{
	void				*data;
	struct s_list_node	*next;
}						t_list_node;

void					ft_lstadd_back(t_list_node **lst,
							t_list_node *new_node);
void					ft_lstadd_front(t_list_node **alst,
							t_list_node *new_node);
void					ft_lstclear(t_list_node **lst, void (*del)(void *));
void					ft_lstdelone(t_list_node *lst, void (*del)(void *));
void					ft_lstiter(t_list_node *lst, void (*f)(void *));
t_list_node				*ft_lstlast(t_list_node *lst);
t_list_node				*ft_lstmap(t_list_node *lst, void *(*f)(void *));
t_list_node				*ft_lstnew(void *data);
int						ft_lstsize(t_list_node *lst);

#endif
