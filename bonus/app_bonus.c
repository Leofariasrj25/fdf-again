/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:01:26 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/03 12:54:54 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "../mlx/mlx.h" 

void	app_run(t_app *data)
{
	mlx_hook(data->window, KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->window, CLOSE_WIN, 1L << 17, close_button, data);
	mlx_hook(data->window, MOUSE_PRESS, 1L << 2, mouse_press, data);
	mlx_hook(data->window, MOUSE_RELEASE, 1L << 3, mouse_release, data);
	mlx_hook(data->window, MOUSE_MOVE, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->mlx, render_scene, data);
	mlx_loop(data->mlx);
}

int	mlx_load(t_app *app_data)
{
	app_data->mlx = mlx_init();
	app_data->window = mlx_new_window(app_data->mlx, \
		SCREEN_W, \
		SCREEN_L, \
		"FdF - lfarias-");
	app_data->win_close = 0;
	app_data->bitmap = malloc(sizeof(t_frame));
	app_data->bitmap->img = mlx_new_image(app_data->mlx, SCREEN_W, SCREEN_L);
	app_data->bitmap->addr = mlx_get_data_addr(app_data->bitmap->img, \
		&app_data->bitmap->bits_per_pixel, \
		&app_data->bitmap->line_length, \
		&app_data->bitmap->endian);
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
}
