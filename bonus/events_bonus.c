/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 20:35:11 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/05 14:50:19 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "../mlx/mlx.h"

void	view_modes(int keycode, t_app *app_data);
void	zscale_change(int keycode, t_app *app_data);
void	xyscale_change(int keycode, t_app *app_data);
void	rotate(int keycode, t_app *app_data);

int	key_press(int keycode, void *param)
{
	t_app	*app_data;

	app_data = (t_app *) param;
	if (keycode == ESC_KEY)
	{
		all_you_need_is_kill(app_data);
		exit(0);
	}
	else if (keycode == F_KEY)
		app_data->fit = 1;
	else if (keycode == I_KEY || keycode == P_KEY)
		view_modes(keycode, app_data);
	else if (keycode == J_KEY || keycode == K_KEY)
		zscale_change(keycode, app_data);
	else if (keycode == H_KEY || keycode == L_KEY)
		xyscale_change(keycode, app_data);
	else if (keycode == ARROW_UP || keycode == ARROW_DOWN \
		|| keycode == ARROW_RIGHT || keycode == ARROW_LEFT \
		|| keycode == Q_KEY || keycode == E_KEY)
		rotate(keycode, app_data);
	else if (keycode == PALETTE_1 || keycode == PALETTE_2 \
		|| keycode == PALETTE_3)
		change_palette(keycode, app_data);
	return (0);
}

void	view_modes(int keycode, t_app *app_data)
{
	if (keycode == I_KEY)
	{
		app_data->isometric = 1;
		app_data->parallel = 0;
		app_data->map_draw = 0;
	}
	else if (keycode == P_KEY)
	{
		app_data->parallel = 1;
		app_data->map_draw = 0;
	}
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
		limit = app_data->map->scale - 0.2;
		if (limit >= 0.0)
			app_data->map->scale = limit;
	}
	else if (keycode == L_KEY)
		app_data->map->scale = app_data->map->scale + 0.2;
	app_data->map_draw = 0;
}

void	rotate(int keycode, t_app *app_data)
{
	if (keycode == ARROW_UP)
		app_data->map->angles[X] = app_data->map->angles[X] - 1.2;
	else if (keycode == ARROW_DOWN)
		app_data->map->angles[X] = app_data->map->angles[X] + 1.2;
	else if (keycode == ARROW_RIGHT)
		app_data->map->angles[Y] = app_data->map->angles[Y] - 1.2;
	else if (keycode == ARROW_LEFT)
		app_data->map->angles[Y] = app_data->map->angles[Y] + 1.2;
	else if (keycode == Q_KEY)
		app_data->map->angles[Z] = app_data->map->angles[Z] + 1.2;
	else if (keycode == E_KEY)
		app_data->map->angles[Z] = app_data->map->angles[Z] - 1.2;
	app_data->map_draw = 0;
}
