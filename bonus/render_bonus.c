/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :::      ::::::::   */
/*                                                    :::      :::     */
/*   By: lfarias- <lfarias-@student.42.rio>         :::   :::   :::        */
/*                                                https://github.com/lfariasr */
/*                                                    https://42.rio         */
/*   Created: 2022/10/13 16:43:25 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/18 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	render_loop(void *param)
{
	t_app	*app;
	int32_t	mx;
	int32_t	my;

	app = (t_app *)param;
	if (app->map_draw)
	{
		if (mlx_is_mouse_down(app->mlx, MLX_MOUSE_BUTTON_RIGHT))
		{
			mlx_get_mouse_pos(app->mlx, &mx, &my);
			app->map->source.x = mx - app->offset_px;
			app->map->source.y = my - app->offset_py;
			display_img(app);
		}
	}
	else
	{
		if (!app->map || !app->map->points)
			return ;
		if (app->projection == NULL)
			app->projection = malloc(sizeof(t_coord) * app->map->size);
		if (!app->projection)
			return ;
		copy_points(app->projection, app->map->points, app->map->size);
		render_img(app, app->projection);
		if (app->fit)
		{
			fit_img(app, app->projection);
			app->fit = 0;
		}
		display_img(app);
		app->map_draw = 1;
	}
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