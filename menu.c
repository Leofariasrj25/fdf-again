/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:49:31 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/03 19:19:08 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MENU_LINE_HEIGHT 20
#define MENU_LINE_MARGIN 20

void	write_map_info(t_app *data);
void	write_controls(t_app *data);
void	draw_key_value(t_app *data, t_coord *point, char *key, char *value);

void	draw_menu(t_app *data)
{
	int		i;
	t_coord	p0;
	t_coord	p1;

	i = 0;
	while (i < SCREEN_L)
	{
		p0.x = 0;
		p0.y = i;
		p0.z = 0;
		p1.x = MENU_WIDTH;
		p1.y = i;
		p1.z = 0;
		draw_line(data->bitmap, &p0, &p1, MENU_BG_COLOR);
		i++;
	}
}

void	write_key_value(t_app *data, t_coord *point, char *key, char *value)
{
	print_str(data, point, MENU_KEY_COLOR, key);
	point->x = 140;
	print_str(data, point, MENU_VALUE_COLOR, value);
	point->y = point->y + MENU_LINE_HEIGHT;
	point->x = MENU_LINE_HEIGHT;
}

void	write_controls(t_app *data)
{
	t_coord	point;

	point.x = MENU_LINE_MARGIN;
	point.y = 300;
	print_str(data, &point, MENU_KEY_COLOR, " ==== CONTROLS ==== ");
	point.y = point.y + MENU_LINE_HEIGHT;
	print_str(data, &point, MENU_KEY_COLOR, "ESC : CLOSE");
	point.y = point.y + MENU_LINE_HEIGHT;
	print_str(data, &point, MENU_KEY_COLOR, "F : FIT MAP");
	point.y = point.y + MENU_LINE_HEIGHT;
	print_str(data, &point, MENU_KEY_COLOR, "J/K : -/+ Z_SCALE");
	point.y = point.y + MENU_LINE_HEIGHT;
	print_str(data, &point, MENU_KEY_COLOR, "H/L : -/+ XY_SCALE");
}

void	write_map_info(t_app *data)
{
	t_coord	point;
	char	*value;

	point.x = 20;
	point.y = 100;
	print_str(data, &point, MENU_KEY_COLOR, " ==== MAP INFO ==== ");
	point.y = point.y + MENU_LINE_HEIGHT;
	write_key_value(data, &point, "NAME :", data->map->name);
	value = ft_itoa(data->map->size);
	write_key_value(data, &point, "SIZE :", value);
	free(value);
	value = ft_itoa(data->map->width);
	write_key_value(data, &point, "LENGTH (X) :", value);
	free(value);
	value = ft_itoa(data->map->length);
	write_key_value(data, &point, "HEIGHT (Y):", value);
	free(value);
	value = ft_itoa(data->map->max_depth);
	write_key_value(data, &point, "+WIDTH (Z) :", value);
	free(value);
	value = ft_itoa(data->map->min_depth);
	write_key_value(data, &point, "-WIDTH (Z) :", value);
	free(value);
}
