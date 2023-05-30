/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:37:46 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/03 19:00:26 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
#include "mlx/mlx.h"

void	print_str(t_app *data, t_coord *point, int color, char *str)
{
	mlx_string_put(data->mlx, data->window, point->x, point->y, color, str);
}

void	print_err_msg(char	*err_msg)
{
	char	*error;

	error = ft_strjoin("[error]: ", err_msg);
	ft_putendl_fd(error, 2);
	free(error);
}

void	free_2d_array(void **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

t_coord	*copy_points(t_coord *dst, t_coord *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i].x = src[i].x;
		dst[i].y = src[i].y;
		dst[i].z = src[i].z;
		dst[i].color = src[i].color;
		i++;
	}
	return (dst);
}

int	atohex(char *str)
{
	static int	hex_values[6] = {10, 11, 12, 13, 14, 15};
	int			nbr;
	int			i;

	if (!str)
		return (0);
	nbr = 0;
	i = 0;
	if (ft_strncmp(str, "0x", 2) == 0 || ft_strncmp(str, "0X", 2) == 0)
		i += 2;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			nbr = nbr * 16 + (str[i] - 48);
		else if (str[i] >= 'a' && str[i] <= 'f')
			nbr = nbr * 16 + hex_values[(str[i] - 97)];
		else if (str[i] >= 'A' && str[i] <= 'F')
			nbr = nbr * 16 + hex_values[(str[i] - 65)];
		i++;
	}
	return (nbr);
}
