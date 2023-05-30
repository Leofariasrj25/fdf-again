/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:21:10 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/03 20:04:14 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		color_pick(t_app *app, t_coord *p0, t_coord *p1);
void	draw_last_line(t_app *data, t_coord *projection);
void	draw_last_col(t_app *data, t_coord *projection);

void	draw_map(t_app *data, t_coord *projection)
{
	int		i;
	int		j;
	int		color;

	i = -1;
	j = 1;
	while (++i < (data->map->size - data->map->width - 1))
	{
		if (i < (data->map->width * j - 1))
		{
			color = color_pick(data, &data->map->points[i], \
				&data->map->points[i + 1]);
			draw_line(data->bitmap, &projection[i], \
					&projection[i + 1], color);
			color = color_pick(data, &projection[i], \
				&projection[i + data->map->width]);
			draw_line(data->bitmap, &projection[i], \
				&projection[i + data->map->width], color);
		}
		else
			j++;
	}
	draw_last_col(data, projection);
	draw_last_line(data, projection);
	draw_menu(data);
}

int	color_pick(t_app *data, t_coord *p0, t_coord *p1)
{
	int	top_area;

	top_area = data->map->max_depth - 4;
	if (p0->color != 0)
		return (p0->color);
	if (p0->z >= top_area && p1->z >= top_area)
		return (0xFF0000);
	if ((p0->z > 0 && p0->z < top_area) || \
			(p1->z > 0 && p1->z < top_area))
		return (0xFF0000);
	if (p0->z <= 0 || (p0->z >= top_area && p1->z <= 0))
		return (0x20C20E);
	return (0xFFFFFF);
}

void	draw_last_line(t_app *data, t_coord *projection)
{
	int	i;
	int	color;

	i = (data->map->size - data->map->width);
	while (i < (data->map->size - 1))
	{
		color = color_pick(data, &data->map->points[i], \
				&data->map->points[i + 1]);
		draw_line(data->bitmap, &projection[i], &projection[i + 1], color);
		i++;
	}
}

void	draw_last_col(t_app *data, t_coord *projection)
{
	int	i;
	int	color;

	i = data->map->width - 1;
	while (i < data->map->size - 1)
	{
		color = color_pick(data, &data->map->points[i], \
			&data->map->points[i + data->map->width]);
		draw_line(data->bitmap, &projection[i], \
			&projection[i + data->map->width], color);
		i += data->map->width;
	}
}
