/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :::      ::::::::   */
/*                                                    :::      ::::::::   */
/*   By: lfarias- <lfarias-@student.42.rio>         :::   :::   :::        */
/*                                                https://github.com/lfariasr */
/*                                                    https://42.rio         */
/*   Created: 2022/10/13 16:43:25 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/17 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app->map_draw)
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
	z_scale(projection, data->map->z_scale, data->map->size);
	isometric(projection, data->map->size);
	scale(projection, data->map->scale, data->map->size);
	translate(projection, &data->map->source, data->map->size);
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
	data->map->source.x = ((SCREEN_W - MENU_WIDTH) / 4) + MENU_WIDTH;
	data->map->source.y = SCREEN_L / 2;
	data->map->source.z = 0;
	copy_points(projection, data->map->points, data->map->size);
	render_img(data, projection);
	while (on_limits(data, projection))
	{
		data->map->scale = data->map->scale + 0.2;
		copy_points(projection, data->map->points, data->map->size);
		render_img(data, projection);
	}
}