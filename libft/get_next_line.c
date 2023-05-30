/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:27:50 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/19 20:51:50 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_str_buff	*create_node(void *content, size_t content_size, size_t lf_count)
{
	t_str_buff	*new_node;

	if (!content)
		return (NULL);
	new_node = malloc(sizeof(t_str_buff));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->start = 0;
	new_node->len = content_size;
	new_node->lf_count = lf_count;
	new_node->next = NULL;
	return (new_node);
}

void	add_node(t_str_buff **str_buff, t_str_buff *node)
{
	t_str_buff	*c_node;

	if (!str_buff || !node)
		return ;
	if (!(*str_buff) && node)
	{
		*str_buff = node;
		node->next = NULL;
		return ;
	}
	c_node = *str_buff;
	while (c_node->next)
	{
		c_node = c_node->next;
	}	
	c_node->next = node;
	node->next = NULL;
}

int	copy_to_str(t_str_buff *node, char *str, int str_index, int str_size)
{
	size_t	i;

	i = node->start;
	while (str_index < str_size && i < node->len)
	{
		str[str_index] = node->content[i];
		i++;
		str_index++;
		node->start++;
	}
	return (str_index);
}

char	*get_line(t_str_buff **str_bf)
{
	char		*new_line;
	t_str_buff	*node;
	size_t		str_size;
	size_t		i;

	str_size = get_strlen(str_bf);
	if (str_size == 0)
		return (NULL);
	new_line = malloc((str_size + 1) * sizeof(char));
	node = *str_bf;
	i = 0;
	while (node != NULL && i < str_size)
	{
		i = copy_to_str(node, new_line, i, str_size);
		if (node->start >= node->len)
			node = next_node(node);
	}
	new_line[str_size] = '\0';
	if (node)
		node->lf_count = node->lf_count - 1;
	*str_bf = node;
	return (new_line);
}

char	*get_next_line(int fd)
{
	char				*read_bf;
	static t_str_buff	*str_bf[MAX_FD] = {0};
	int					bytes_read;

	if (BUFFER_SIZE <= 0 || (fd < 0 || fd > MAX_FD))
		return (NULL);
	bytes_read = -1;
	while (bytes_read != 0)
	{
		if (check_list(&str_bf[fd]))
			break ;
		read_bf = malloc(BUFFER_SIZE);
		bytes_read = read(fd, read_bf, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(read_bf);
			break ;
		}
		add_node(&str_bf[fd],
			create_node(read_bf, bytes_read, count_lf(read_bf, bytes_read)));
	}
	return (get_line(&str_bf[fd]));
}
