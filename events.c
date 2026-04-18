/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :::      ::::::::   */
/*                                                    :::      ::::::::   */
/*   By: lfarias- <lfarias-@student.42.rio>         :::   :::   :::        */
/*                                                https://github.com/lfariasr */
/*                                                    https://42.rio         */
/*   Created: 2022/10/24 20:35:11 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/17 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zscale_change(int keycode, t_app *app_data);
static void	xyscale_change(int keycode, t_app *app_data);

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
	{
		app->fit = 1;
		app->map_draw = 0;
	}
	if ((keydata.key == MLX_KEY_J || keydata.key == MLX_KEY_K) \
		&& keydata.action == MLX_PRESS)
		zscale_change(keydata.key, app);
	if ((keydata.key == MLX_KEY_H || keydata.key == MLX_KEY_L) \
		&& keydata.action == MLX_PRESS)
		xyscale_change(keydata.key, app);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		all_you_need_is_kill(app);
		exit(0);
	}
}

void	close_handler(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	all_you_need_is_kill(app);
	exit(0);
}

static void	zscale_change(int keycode, t_app *app_data)
{
	if (keycode == MLX_KEY_J)
		app_data->map->z_scale = app_data->map->z_scale + 0.2;
	else if (keycode == MLX_KEY_K)
		app_data->map->z_scale = app_data->map->z_scale - 0.2;
	app_data->map_draw = 0;
}

static void	xyscale_change(int keycode, t_app *app_data)
{
	double	limit;

	limit = 0.0;
	if (keycode == MLX_KEY_H)
	{
		limit = app_data->map->scale - 0.5;
		if (limit >= 0.0)
			app_data->map->scale = limit;
	}
	else if (keycode == MLX_KEY_L)
		app_data->map->scale = app_data->map->scale + 0.5;
	app_data->map_draw = 0;
}