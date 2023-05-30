/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:43:25 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/03 18:50:20 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "../mlx/mlx.h"

t_frame	*get_new_img(t_app *app_data);

int	render_scene(t_app *app_data)
{
	t_frame	*screen;

	if (app_data->projection == NULL)
		app_data->projection = malloc(sizeof(t_coord) * app_data->map->size);
	if (!app_data->win_close && !app_data->map_draw)
	{
		screen = get_new_img(app_data);
		if (!app_data->map_draw)
		{
			copy_points(app_data->projection, app_data->map->points, \
				app_data->map->size);
			render_img(app_data, app_data->projection);
		}
		if (app_data->fit)
		{
			fit_img(app_data, app_data->projection);
			app_data->fit = 0;
		}
		display_img(app_data);
		app_data->map_draw = 1;
		free_img_buffer(app_data, screen);
	}
	return (0);
}

t_frame	*get_new_img(t_app *app_data)
{
	t_frame	*screen;

	screen = NULL;
	if (!app_data->map_draw)
	{
		screen = app_data->bitmap;
		app_data->bitmap = malloc(sizeof(t_frame));
		app_data->bitmap->img = mlx_new_image(app_data->mlx, \
			SCREEN_W, SCREEN_L);
		app_data->bitmap->addr = mlx_get_data_addr(app_data->bitmap->img, \
			&app_data->bitmap->bits_per_pixel, \
			&app_data->bitmap->line_length, \
			&app_data->bitmap->endian);
		return (screen);
	}
	else
		return (screen);
}

void	render_img(t_app *data, t_coord *projection)
{
	int	size;

	size = data->map->size;
	z_scale(projection, data->map->z_scale, size);
	if (data->isometric)
		isometric(projection, size);
	if (data->parallel)
		copy_points(projection, data->map->points, size);
	rotate_x(projection, data->map->angles[X], size);
	rotate_y(projection, data->map->angles[Y], size);
	rotate_z(projection, data->map->angles[Z], size);
	scale(projection, data->map->scale, size);
	translate(projection, &data->map->source, size);
}

int	on_limits(t_app *data, t_coord *points)
{
	int		i;
	int		canvas_width;
	int		canvas_length;

	i = 0;
	canvas_width = SCREEN_W - CANVAS_MARGIN;
	canvas_length = SCREEN_L - CANVAS_MARGIN;
	while (i < data->map->size)
	{	
		if (points[i].x < (MENU_WIDTH + CANVAS_MARGIN) \
			|| points[i].x >= canvas_width)
			return (0);
		if (points[i].y < CANVAS_MARGIN \
			|| points[i].y >= canvas_length)
			return (0);
		i++;
	}
	return (1);
}

void	fit_img(t_app *data, t_coord *projection)
{
	data->map->scale = 1;
	data->map->z_scale = 0.5;
	data->map->source.x = ((SCREEN_W - MENU_WIDTH) / 2) + MENU_WIDTH;
	data->map->source.y = SCREEN_L / 2;
	data->map->source.z = 0.1;
	data->map->angles[X] = 0;
	data->map->angles[Y] = 0;
	data->map->angles[Z] = 0;
	copy_points(projection, data->map->points, data->map->size);
	render_img(data, projection);
	while (on_limits(data, projection))
	{
		data->map->scale = data->map->scale + 0.2;
		copy_points(projection, data->map->points, data->map->size);
		render_img(data, projection);
	}
}
