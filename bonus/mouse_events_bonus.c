/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_bonus.c                               :::      ::::::::   */
/*                                                    :::      :::     */
/*   By: lfarias- <lfarias-@student.42.rio>         #+# #+#  #+#             */
/*                                                ./+#+#.+#.#+.##.#+.##.#+ */
/*   Created: 2022/10/29 01:08:12 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/18 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	zoom_img(int x, int y, double scale, t_app *app_data)
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

void	mouse_press_handler(mouse_key_t button, action_t action, \
	modifier_key_t mods, void *param)
{
	t_app	*app_data;
	int32_t	mx;
	int32_t	my;

	app_data = (t_app *)param;
	(void)mods;
	mlx_get_mouse_pos(app_data->mlx, &mx, &my);
	if (action == MLX_PRESS)
	{
		if (button == MLX_MOUSE_BUTTON_RIGHT)
		{
			app_data->mouse_r_press = 1;
			app_data->offset_px = mx - app_data->map->source.x;
			app_data->offset_py = my - app_data->map->source.y;
		}
		if (button == MLX_MOUSE_BUTTON_LEFT)
			app_data->mouse_l_press = 1;
	}
	else if (action == MLX_RELEASE)
	{
		if (button == MLX_MOUSE_BUTTON_RIGHT)
			app_data->mouse_r_press = 0;
		if (button == MLX_MOUSE_BUTTON_LEFT)
			app_data->mouse_l_press = 0;
	}
}

void	cursor_move_handler(double x, double y, void *param)
{
	t_app	*app_data;

	app_data = (t_app *)param;
	(void)x;
	(void)y;
	if (app_data->mouse_r_press == 1)
	{
		app_data->map->source.x = x - app_data->offset_px;
		app_data->map->source.y = y - app_data->offset_py;
		app_data->map_draw = 0;
	}
}

void	scroll_handler(double xdelta, double ydelta, void *param)
{
	t_app	*app_data;
	int32_t	x;
	int32_t	y;

	app_data = (t_app *)param;
	(void)xdelta;
	mlx_get_mouse_pos(app_data->mlx, &x, &y);
	if (ydelta > 0)
		zoom_img(x, y, 1.0, app_data);
	else if (ydelta < 0)
		zoom_img(x, y, -0.9, app_data);
	app_data->map_draw = 0;
}