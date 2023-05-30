/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:43:58 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/03 18:55:58 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"

void	free_img_buffer(t_app *app_data, t_frame *screen)
{
	if (screen != NULL)
	{
		mlx_destroy_image(app_data->mlx, screen->img);
		free(screen);
	}
}

void	display_img(t_app *app_data)
{
	draw_map(app_data, app_data->projection);
	mlx_put_image_to_window(app_data->mlx, app_data->window, \
		app_data->bitmap->img, 0, 0);
	write_map_info(app_data);
	write_controls(app_data);
}
