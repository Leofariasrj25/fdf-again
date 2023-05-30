/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:54:48 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/19 20:52:14 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	count_lf(char *read_bf, size_t bytes_read)
{
	size_t		i;
	size_t		lf_count;

	i = 0;
	lf_count = 0;
	while (i < bytes_read)
	{
		if (read_bf[i] == LF)
			lf_count++;
		i++;
	}
	return (lf_count);
}

int	get_strlen(t_str_buff **str_bf)
{
	t_str_buff	*node;
	size_t		i;
	size_t		len;

	if (!str_bf || !(*str_bf))
		return (0);
	node = *str_bf;
	len = 0;
	i = 0;
	while (node != NULL)
	{
		i = node->start;
		while (i < node->len && node->content[i])
		{
			len++;
			if (node->content[i] == '\n')
				break ;
			i++;
		}
		node = node->next;
	}
	return (len);
}

t_str_buff	*next_node(t_str_buff *node)
{
	t_str_buff	*next_node;

	if (node)
	{
		next_node = node->next;
		free(node->content);
		free(node);
		return (next_node);
	}
	else
		return (NULL);
}

int	check_list(t_str_buff **list)
{
	t_str_buff	*node;

	node = *list;
	while (node)
	{
		if (node->lf_count > 0)
			return (1);
		node = node->next;
	}
	return (0);
}
