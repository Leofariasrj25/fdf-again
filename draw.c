/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :::      ::::::::   */
/*                                                    :::      ::::::::   */
/*   By: lfarias- <lfarias-@student.42.rio>         :::   :::   :::        */
/*                                                https://github.com/lfariasr */
/*                                                    https://42.rio         */
/*   Created: 2022/09/25 17:20:22 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/17 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

#define X 0
#define Y 1

void	draw_low_line(mlx_image_t *img, t_coord *p0, t_coord *p1, uint32_t color);
void	draw_high_line(mlx_image_t *img, t_coord *p0, t_coord *p1, uint32_t color);
void	setup_vars(int delta[2], int axis[2], t_coord *p0, t_coord *p1);

void	draw_line(mlx_image_t *img, t_coord *point0, t_coord *point1, uint32_t color)
{
	if (out_of_screen(point0, point1))
		return ;
	if (fabs(point1->y - point0->y) < fabs(point1->x - point0->x))
	{
		if (point0->x > point1->x)
			draw_low_line(img, point1, point0, color);
		else
			draw_low_line(img, point0, point1, color);
	}
	else
	{
		if (point0->y > point1->y)
			draw_high_line(img, point1, point0, color);
		else
			draw_high_line(img, point0, point1, color);
	}
}

void	setup_vars(int delta[2], int axis[2], t_coord *p0, t_coord *p1)
{
	delta[X] = p1->x - p0->x;
	delta[Y] = p1->y - p0->y;
	axis[Y] = p0->y;
	axis[X] = p0->x;
}

void	draw_low_line(mlx_image_t *img, t_coord *point0, t_coord *point1, uint32_t color)
{
	int	delta[2];
	int	axis[2];
	int	d_factor;
	int	yi;

	setup_vars(delta, axis, point0, point1);
	yi = 1;
	if (delta[Y] < 0)
	{
		yi = -1;
		delta[Y] = delta[Y] * -1;
	}
	d_factor = (2 * delta[Y]) - delta[X];
	while (axis[X] < point1->x && on_screen(axis[X], axis[Y]))
	{
		mlx_put_pixel(img, round_to_i(axis[X]), round_to_i(axis[Y]), color);
		if (d_factor > 0)
		{
			axis[Y] = axis[Y] + yi;
			d_factor = d_factor + (2 * (delta[Y] - delta[X]));
		}
		else
			d_factor = d_factor + 2 * delta[Y];
		axis[X] = axis[X] + 1;
	}
}

void	draw_high_line(mlx_image_t *img, t_coord *p0, t_coord *p1, uint32_t color)
{
	int	delta[2];
	int	axis[2];
	int	d_factor;
	int	xi;

	setup_vars(delta, axis, p0, p1);
	xi = 1;
	if (delta[X] < 0)
	{
		xi = -1;
		delta[X] = delta[X] * -1;
	}
	d_factor = (2 * delta[X]) - delta[Y];
	while (axis[Y] < p1->y && on_screen(axis[X], axis[Y]))
	{
		mlx_put_pixel(img, round_to_i(axis[X]), round_to_i(axis[Y]), color);
		if (d_factor > 0)
		{
			axis[X] = axis[X] + xi;
			d_factor = d_factor + (2 * (delta[X] - delta[Y]));
		}
		else
			d_factor = d_factor + 2 * delta[X];
		axis[Y] = axis[Y] + 1;
	}
}