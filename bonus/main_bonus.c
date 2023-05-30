/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:40:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/01 19:06:58 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	t_app	app_data;

	if (!check_input_size(argc))
		return (1);
	app_data.map = map_get(argv[1]);
	if (!app_data.map)
		return (1);
	mlx_load(&app_data);
	vars_load(&app_data, argc, argv);
	app_run(&app_data);
	return (0);
}
