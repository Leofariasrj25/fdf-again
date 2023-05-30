/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:09:30 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/03 18:01:26 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	close_button(void *param)
{
	t_app	*app_data;

	app_data = (t_app *) param;
	all_you_need_is_kill(app_data);
	exit(0);
}

int	change_palette(int keycode, t_app *app_data)
{
	if (keycode == PALETTE_1)
	{
		app_data->base_color = 0x4B4B4B;
		app_data->medium_color = 0xC4C4C4;
		app_data->top_color = 0xff9001;
	}
	if (keycode == PALETTE_2)
	{
		app_data->base_color = 0x6600cc;
		app_data->medium_color = 0x9900cc;
		app_data->top_color = 0xcc00cc;
	}
	if (keycode == PALETTE_3)
	{
		app_data->base_color = 0x20C20E;
		app_data->medium_color = 0x20C20E;
		app_data->top_color = 0x20C20E;
	}
	app_data->color_palette = 1;
	app_data->map_draw = 0;
	return (0);
}
