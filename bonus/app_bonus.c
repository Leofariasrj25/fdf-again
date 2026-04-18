/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_bonus.c                                        :::      ::::::::   */
/*                                                    :::      ::::::::   */
/*   By: lfarias- <lfarias-@student.42.rio>         :::   :::   :::        */
/*                                                https://github.com/lfariasr */
/*                                                    https://42.rio         */
/*   Created: 2022/10/28 16:01:26 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/17 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	app_run(t_app *data)
{
	mlx_key_hook(data->mlx, key_handler, data);
	mlx_close_hook(data->mlx, close_handler, data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	mlx_mouse_hook(data->mlx, mouse_press_handler, data);
	mlx_cursor_hook(data->mlx, cursor_move_handler, data);
	mlx_scroll_hook(data->mlx, scroll_handler, data);
	mlx_loop_hook(data->mlx, render_loop, data);
	mlx_loop(data->mlx);
}

int	mlx_load(t_app *app_data)
{
	int	i;

	app_data->mlx = mlx_init(SCREEN_W, SCREEN_L, "FdF - lfarias-", true);
	if (!app_data->mlx)
		return (1);
	app_data->img = mlx_new_image(app_data->mlx, SCREEN_W, SCREEN_L);
	if (!app_data->img)
		return (1);
	mlx_image_to_window(app_data->mlx, app_data->img, 0, 0);
	i = 0;
	while (i < 20)
	{
		app_data->str_img[i] = NULL;
		i++;
	}
	app_data->str_count = 0;
	app_data->map_draw = 0;
	return (0);
}

void	vars_load(t_app *app_data, int argc, char **argv)
{
	app_data->projection = NULL;
	app_data->fit = 0;
	app_data->map_draw = 0;
	app_data->map->scale = get_scale(app_data->map->width, \
		app_data->map->length, \
		argc, \
		argv);
	app_data->map->z_scale = get_z_scale(argc, argv);
	app_data->map->source.x = ((SCREEN_W - MENU_WIDTH) / 2) + MENU_WIDTH;
	app_data->map->source.y = SCREEN_L / 2;
	app_data->map->source.z = -100;
	app_data->map->angles[X] = 0;
	app_data->map->angles[Y] = 0;
	app_data->map->angles[Z] = 0;
	app_data->base_color = 0x4B4B4B;
	app_data->medium_color = 0xC4C4C4;
	app_data->top_color = 0xff9001;
	app_data->parallel = 0;
	app_data->isometric = 1;
	app_data->mouse_l_press = 0;
	app_data->mouse_r_press = 0;
	app_data->offset_px = 0;
	app_data->offset_py = 0;
}