/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_input_bonus.c                                  :::      ::::::::   */
/*                                                    :::      ::::::::   */
/*   By: lfarias- <lfarias-@student.42.rio>         :::   :::   :::        */
/*                                                https://github.com/lfariasr */
/*                                                    https://42.rio         */
/*   Created: 2022/10/24 20:36:22 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/17 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

double	get_scale(int map_width, int map_length, int argc, char **argv)
{
	double	scale_x;
	double	scale_y;

	if ((argc - 1) == 3)
	{
		return (ft_atoi(argv[2]));
	}
	else
	{
		scale_x = 320 / (double) map_width;
		scale_y = 240 / (double) map_length;
		if (scale_x > scale_y)
			return (scale_x);
		else
			return (scale_y);
	}
}

double	get_z_scale(int argc, char **argv)
{
	if ((argc - 1) == 3)
	{
		return (ft_atoi(argv[3]));
	}
	else
		return (0.5);
}

int	check_input_size(int argc)
{
	char	*usage;

	usage = "Usage: ./fdf <filename> [ scale z_size ]";
	if (!((argc - 1) == 1 || (argc - 1) == 3))
	{
		ft_putendl_fd(usage, 1);
		return (0);
	}
	return (1);
}

void	all_you_need_is_kill(t_app *app_data)
{
	int	i;

	i = 0;
	while (i < app_data->str_count)
	{
		if (app_data->str_img[i])
		{
			mlx_delete_image(app_data->mlx, app_data->str_img[i]);
			app_data->str_img[i] = NULL;
		}
		i++;
	}
	mlx_delete_image(app_data->mlx, app_data->img);
	mlx_terminate(app_data->mlx);
	free(app_data->map->points);
	if (app_data->projection)
		free(app_data->projection);
	free(app_data->map);
}