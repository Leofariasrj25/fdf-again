/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:25:35 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/28 16:08:44 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "math.h"

double	dg2_rad(double angle)
{
	static const double	pi = 3.14159;

	return (pi * angle / (double) 180.00);
}

int	round_to_i(double value)
{
	int	rounded;

	rounded = (value / 1);
	if (fmod(value, 1) >= 0.5)
		return (rounded + 1);
	else
		return (rounded);
}
