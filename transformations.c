/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:19:28 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/30 11:21:40 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"

#define COS 0
#define SIN 1
#define ISO_ANGLE 330
#define ISO_ROT 60

void	isometric(t_coord *point, int size)
{
	int		i;
	t_coord	holder;
	double	cos_sin_angle[2];	
	double	cos_sum_diff[2];
	double	sin_sum_diff[2];

	cos_sin_angle[COS] = cos(dg2_rad(ISO_ANGLE));
	cos_sin_angle[SIN] = sin(dg2_rad(ISO_ANGLE));
	cos_sum_diff[0] = cos(dg2_rad(ISO_ANGLE) + dg2_rad(ISO_ROT));
	cos_sum_diff[1] = cos(dg2_rad(ISO_ANGLE) - dg2_rad(ISO_ROT));
	sin_sum_diff[0] = sin(dg2_rad(ISO_ANGLE) + dg2_rad(ISO_ROT));
	sin_sum_diff[1] = sin(dg2_rad(ISO_ANGLE) - dg2_rad(ISO_ROT));
	i = -1;
	while (++i < size)
	{
		holder.x = point[i].x;
		holder.y = point[i].y;
		holder.z = point[i].z;
		point[i].x = holder.x * cos_sin_angle[COS] + holder.y * cos_sum_diff[0] \
			+ holder.z * cos_sum_diff[1];
		point[i].y = holder.x * cos_sin_angle[SIN] + holder.y * sin_sum_diff[0] \
			+ holder.z * sin_sum_diff[1];
	}
}

void	scale(t_coord *point, double scale, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		point[i].x = point[i].x * scale;
		point[i].y = point[i].y * scale;
		point[i].z = point[i].z * scale;
		i++;
	}
}

void	translate(t_coord *point, t_coord *move, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		point[i].x = point[i].x + move->x;
		point[i].y = point[i].y + move->y;
		point[i].z = point[i].z + move->z;
		i++;
	}
}

void	z_scale(t_coord *projection, double z_scale, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		projection[i].z = (double) projection[i].z * z_scale;
		i++;
	}
}
