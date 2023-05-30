/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:25:55 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/03 13:57:13 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <math.h>

void	rotate_x(t_coord *points, double angle, int size)
{
	double	cos_theta;
	double	sin_theta;
	t_coord	holder;
	t_coord	offset;
	int		i;

	cos_theta = cos(dg2_rad(angle));
	sin_theta = sin(dg2_rad(angle));
	offset.y = points[size / 2].y;
	offset.z = points[size / 2].z;
	i = 0;
	while (i < size)
	{
		holder.y = points[i].y - offset.y;
		holder.z = points[i].z - offset.z;
		points[i].y = (holder.y * cos_theta) - (holder.z * sin_theta);
		points[i].z = (holder.y * sin_theta) + (holder.z * cos_theta);
		points[i].y = points[i].y + offset.y;
		points[i].z = points[i].z + offset.z;
		i++;
	}
}

void	rotate_y(t_coord *points, double angle, int size)
{
	double	cos_theta;
	double	sin_theta;
	t_coord	holder;
	t_coord	offset;
	int		i;

	cos_theta = cos(dg2_rad(angle));
	sin_theta = sin(dg2_rad(angle));
	offset.x = points[size / 2].x;
	offset.z = points[size / 2].z;
	i = 0;
	while (i < size)
	{
		holder.x = points[i].x - offset.x;
		holder.z = points[i].z - offset.z;
		points[i].x = (holder.x * cos_theta) + (holder.z * sin_theta);
		points[i].z = (holder.x * (sin_theta * -1)) + (holder.z * cos_theta);
		points[i].x = points[i].x + offset.x;
		points[i].z = points[i].z + offset.z;
		i++;
	}
}

void	rotate_z(t_coord *points, double angle, int size)
{
	double	cos_theta;
	double	sin_theta;
	t_coord	holder;
	t_coord	offset;
	int		i;

	cos_theta = cos(dg2_rad(angle));
	sin_theta = sin(dg2_rad(angle));
	offset.x = points[size / 2].x;
	offset.y = points[size / 2].y;
	i = 0;
	while (i < size)
	{
		holder.x = points[i].x - offset.x;
		holder.y = points[i].y - offset.y;
		points[i].x = (holder.x * cos_theta) - (holder.y * sin_theta);
		points[i].y = (holder.x * sin_theta) + (holder.y * cos_theta);
		holder.x = points[i].x + offset.x;
		holder.z = points[i].y + offset.y;
		i++;
	}
}
