/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:29:11 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/25 13:20:26 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MAX_INT 2147483647
#define MIN_INT -2147483648

int	get_line_size(char **fields)
{
	int		size;

	if (!fields)
		return (0);
	size = 0;
	while (fields[size])
	{
		size++;
	}
	return (size);
}

int	check_line_format(char **fields)
{
	static int	min_len = -1;
	static int	curr_line = -1;
	int			line_len;

	curr_line++;
	line_len = get_line_size(fields);
	if ((line_len == 0 && curr_line == 0)
		|| (fields[0][0] == '\n' && curr_line == 0))
	{
		print_err_msg("No data found");
		return (0);
	}
	if (min_len == -1)
		min_len = line_len;
	if (line_len < min_len)
	{
		print_err_msg("Found wrong line length. Exiting.");
		return (0);
	}
	return (1);
}

void	get_minmax_z(t_map *map)
{
	int	z_negative;
	int	z_positive;
	int	i;

	if (!map)
		return ;
	z_negative = MAX_INT;
	z_positive = MIN_INT;
	i = -1;
	while (++i < map->size)
	{
		if (map->points[i].z < z_negative)
			z_negative = map->points[i].z;
		else if (map->points[i].z > z_positive)
			z_positive = map->points[i].z;
	}
	map->max_depth = z_positive;
	map->min_depth = z_negative;
}

void	erase_lines(t_list *map_line)
{
	t_list	*node;
	t_list	*aux;

	node = map_line;
	while (node)
	{
		free(node->content);
		aux = node;
		node = node->next;
		free(aux);
	}
}
