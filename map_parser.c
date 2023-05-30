/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:15:09 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/24 17:38:07 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <fcntl.h>

int	map_open(char *map_name)
{
	int	fd;

	if (!map_name)
		return (-1);
	fd = open(map_name, O_RDONLY);
	return (fd);
}

t_list	*map_read(int map_fd)
{
	t_list	*map_lines;
	t_list	*node;
	char	*line;

	map_lines = NULL;
	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			break ;
		node = ft_lstnew(line);
		if (map_lines == NULL)
			map_lines = node;
		else
			ft_lstadd_back(&map_lines, node);
	}
	return (map_lines);
}

t_coord	**map_extract_coords(char *line, int line_number)
{
	t_coord		**coord_line;
	t_coord		*coord;
	char		**line_values;
	int			i;

	line_values = ft_split(line, ' ');
	i = 0;
	while (line_values[i])
		i++;
	coord_line = malloc(sizeof(t_coord *) * (i + 1));
	i = 0;
	while (line_values[i])
	{
		coord = malloc(sizeof(t_coord));
		coord->x = i;
		coord->y = line_number;
		coord->z = ft_atoi(line_values[i]);
		coord_line[i] = coord;
		free(line_values[i]);
		i++;
	}
	coord_line[i] = NULL;
	free(line_values);
	return (coord_line);
}

t_coord	***map_parse(t_list *map_lines)
{
	t_coord	***wireframe;
	t_list	*node;
	char	*line;
	int		line_number;
	int		i;

	wireframe = malloc(sizeof(t_coord **) * (ft_lstsize(map_lines) + 1));
	if (!wireframe)
		return (NULL);
	i = 0;
	line_number = 0;
	node = map_lines;
	while (node)
	{
		line = (char *) node->content;
		wireframe[i] = map_extract_coords(line, line_number);
		i++;
		line_number++;
		node = node->next;
	}
	wireframe[i] = NULL;
	return (wireframe);
}

/*#include <stdio.h>

int main(int argc, char *argv[])
{
	char	*filename = argv[1];	
	t_list	*coords;
	int	fd;

	fd = map_open(filename);
	coords = map_read(fd);
	t_coord	***map_coords = map_parse(coords);

	int i = 0;
	while (map_coords[i])
	{
		printf("\t=== line %d ===\n", i);
		int j = 0;
		while (map_coords[i][j])
		{
			printf("=== node %d ===\n", j);
			printf("x: %d\n", map_coords[i][j]->x);
			printf("y: %d\n", map_coords[i][j]->y);
			printf("z: %d\n", map_coords[i][j]->z);
			printf("=\n");
			j++;
		}
		i++;
	}
}*/
