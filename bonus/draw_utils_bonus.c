/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:02:39 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/01 19:43:21 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	on_screen(double x, double y)
{
	if ((x >= 0.0 && x <= (SCREEN_W - CANVAS_MARGIN)) \
		&& (y >= 0.0 && y <= (SCREEN_L - CANVAS_MARGIN)))
		return (1);
	else
		return (0);
}

int	out_of_screen(t_coord *p0, t_coord *p1)
{
	if (!on_screen(p0->x, p0->y) && !on_screen(p1->x, p1->y))
		return (1);
	else
		return (0);
}
