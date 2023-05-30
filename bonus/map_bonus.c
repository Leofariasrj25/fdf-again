/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:15:09 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/28 16:14:08 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "../libft/libft.h"
#include "../libft/get_next_line.h"
#include <fcntl.h>

int		map_open(char *map_name);
t_list	*map_read(int map_fd);
t_coord	*map_extract_coords(t_list *map_lines, int *map_l, int *map_h);

// Manages all of the map reading and conversion logic
t_map	*map_get(char *map_name)
{
	int		map_fd;
	t_map	*map;
	t_list	*map_lines;

	map_fd = map_open(map_name);
	if (map_fd == -1)
		return (NULL);
	map_lines = map_read(map_fd);
	close(map_fd);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->points = map_extract_coords(map_lines, &map->width, &map->length);
	erase_lines(map_lines);
	if (!map->points)
	{
		free(map);
		return (NULL);
	}
	map->size = map->width * map->length;
	get_minmax_z(map);
	map->name = ft_strrchr(map_name, '/');
	if (!map->name)
		map->name = map_name;
	return (map);
}

int	map_open(char *map_name)
{
	int		fd;
	char	*error;

	if (!map_name)
		return (-1);
	error = NULL;
	fd = open(map_name, O_RDONLY);
	if (fd != -1)
		return (fd);
	else
	{
		error = ft_strjoin("fdf: No such file or directory - ", map_name);
		ft_putendl_fd(error, 2);
		free(error);
		return (-1);
	}
}

t_list	*map_read(int map_fd)
{
	t_list	*map_lines;
	t_list	*node;
	char	*line;

	map_lines = NULL;
	node = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			break ;
		else
		{
			node = ft_lstnew(line);
			ft_lstadd_back(&map_lines, node);
		}
	}
	return (map_lines);
}

t_coord	*map_parse(char **fields, t_coord *points)
{	
	static int	line_number;
	static int	p_i;
	int			i;
	char		**z_and_color;

	i = 0;
	while (fields[i])
	{
		z_and_color = ft_split(fields[i], ',');
		points[p_i].x = i;
		points[p_i].y = line_number;
		points[p_i].z = ft_atoi(z_and_color[0]);
		points[p_i].color = atohex(z_and_color[1]);
		free_2d_array((void **) z_and_color);
		p_i++;
		i++;
	}
	free_2d_array((void **) fields);
	line_number++;
	return (points);
}

t_coord	*map_extract_coords(t_list *map_lines, int *map_length, int *map_height)
{
	char	**fields;
	t_coord	*points;

	points = NULL;
	while (map_lines)
	{
		fields = ft_split((char *) map_lines->content, ' ');
		if (!check_line_format(fields))
		{
			free(points);
			free_2d_array((void **) fields);
			return (NULL);
		}
		if (points == NULL)
		{
			*map_length = get_line_size(fields);
			*map_height = ft_lstsize(map_lines);
			points = malloc(sizeof(t_coord) * (*map_length * *map_height));
		}
		map_parse(fields, points);
		map_lines = map_lines->next;
	}
	return (points);
}
