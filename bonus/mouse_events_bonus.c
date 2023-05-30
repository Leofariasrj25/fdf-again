/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 01:08:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/05 14:52:57 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	zoom_img(int x, int y, double scale, t_app *app_data);

int	mouse_press(int button, int x, int y, void *param)
{
	t_app	*app_data;

	app_data = (t_app *) param;
	if (button == 2)
	{
		app_data->mouse_r_press = 1;
		app_data->offset_px = x - app_data->map->source.x;
		app_data->offset_py = y - app_data->map->source.y;
	}
	if (button == 1)
		app_data->mouse_l_press = 1;
	if (button == 4)
		zoom_img(x, y, 1.0, app_data);
	if (button == 5)
		zoom_img(x, y, -0.9, app_data);
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_app	*app_data;

	app_data = (t_app *) param;
	if (app_data->mouse_r_press == 1)
	{
		app_data->map->source.x = x - app_data->offset_px;
		app_data->map->source.y = y - app_data->offset_py;
		app_data->map_draw = 0;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, void *param)
{
	t_app	*app_data;

	x = y;
	y = x;
	app_data = (t_app *) param;
	if (button == 1 && app_data->mouse_r_press == 1)
		app_data->mouse_l_press = 0;
	if (button == 2)
		app_data->mouse_r_press = 0;
	return (0);
}

void	zoom_img(int x, int y, double scale, t_app *app_data)
{
	int	pointer_x;
	int	pointer_y;

	pointer_x = (x - app_data->map->source.x) / app_data->map->scale;
	pointer_y = (y - app_data->map->source.y) / app_data->map->scale;
	if (app_data->map->scale + scale > 0)
		app_data->map->scale = app_data->map->scale + scale;
	else
		return ;
	if (scale < 0)
	{
		app_data->map->source.x = app_data->map->source.x + pointer_x;
		app_data->map->source.y = app_data->map->source.y + pointer_y;
	}
	else if (scale > 0)
	{
		app_data->map->source.x = app_data->map->source.x - pointer_x;
		app_data->map->source.y = app_data->map->source.y - pointer_y;
	}	
	app_data->map_draw = 0;
}
