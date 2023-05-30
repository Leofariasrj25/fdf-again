/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:07:39 by lfarias-          #+#    #+#             */
/*   Updated: 2022/05/15 15:24:08 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!(*lst) && new)
	{
		*lst = new;
		new->next = NULL;
	}
	else if (lst && new)
	{
		last_node = ft_lstlast(*lst);
		last_node->next = new;
		new->next = NULL;
	}
}
