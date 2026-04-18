/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2_bonus.c                                    :::      ::::::::   */
/*                                                    :::      :::     */
/*   By: lfarias- <lfarias-@student.42.rio>         :::   :::   :::        */
/*                                                https://github.com/lfariasr */
/*                                                    https://42.rio         */
/*   Created: 2022/10/26 18:43:58 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/18 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	clear_strings(t_app *app);

void	clear_img(mlx_image_t *img)
{
	int	pixel_count;

	if (!img)
		return ;
	pixel_count = img->width * img->height;
	ft_memset(img->pixels, 0, pixel_count * sizeof(uint32_t));
}

static void	clear_strings(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->str_count)
	{
		if (app->str_img[i])
		{
			mlx_delete_image(app->mlx, app->str_img[i]);
			app->str_img[i] = NULL;
		}
		i++;
	}
	app->str_count = 0;
}

void	display_img(t_app *app_data)
{
	if (!app_data || !app_data->img || !app_data->projection)
		return ;
	clear_img(app_data->img);
	clear_strings(app_data);
	draw_map(app_data, app_data->projection);
	write_map_info(app_data);
	write_controls(app_data);
	write_colorschemes(app_data);
}

void	display_map_only(t_app *app_data)
{
	if (!app_data || !app_data->img || !app_data->projection)
		return ;
	clear_img(app_data->img);
	draw_map(app_data, app_data->projection);
}