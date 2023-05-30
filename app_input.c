/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 20:36:22 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/03 19:03:16 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx/mlx.h"

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
	mlx_destroy_image(app_data->mlx, app_data->bitmap->img);
	free(app_data->bitmap);
	mlx_destroy_window(app_data->mlx, app_data->window);
	app_data->window = NULL;
	app_data->win_close = 1;
	free(app_data->mlx);
	free(app_data->map->points);
	free(app_data->projection);
	free(app_data->map);
}
