/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 20:35:11 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/03 19:20:00 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"

void	zscale_change(int keycode, t_app *app_data);
void	xyscale_change(int keycode, t_app *app_data);

int	key_press(int keycode, void *param)
{
	t_app	*app_data;

	app_data = (t_app *) param;
	if (keycode == F_KEY)
	{
		app_data->fit = 1;
		app_data->map_draw = 0;
	}
	if (keycode == J_KEY || keycode == K_KEY)
		zscale_change(keycode, app_data);
	if (keycode == H_KEY || keycode == L_KEY)
		xyscale_change(keycode, app_data);
	if (keycode == ESC_KEY)
	{
		all_you_need_is_kill(app_data);
		exit(0);
	}
	return (0);
}

int	close_button(void *param)
{
	t_app	*app_data;

	app_data = (t_app *) param;
	all_you_need_is_kill(app_data);
	exit(0);
}

void	zscale_change(int keycode, t_app *app_data)
{
	if (keycode == J_KEY)
		app_data->map->z_scale = app_data->map->z_scale + 0.2;
	else if (keycode == K_KEY)
		app_data->map->z_scale = app_data->map->z_scale - 0.2;
	app_data->map_draw = 0;
}

void	xyscale_change(int keycode, t_app *app_data)
{
	double	limit;

	limit = 0.0;
	if (keycode == H_KEY)
	{
		limit = app_data->map->scale - 0.5;
		if (limit >= 0.0)
			app_data->map->scale = limit;
	}
	else if (keycode == L_KEY)
		app_data->map->scale = app_data->map->scale + 0.5;
	app_data->map_draw = 0;
}
