/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :::      ::::::::   */
/*                                                    :::      ::::::::   */
/*   By: lfarias- <lfarias-@student.42.rio>         :::   :::   :::        */
/*                                                https://github.com/lfariasr */
/*                                                    https://42.rio         */
/*   Created: 2022/10/21 15:49:31 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/17 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

#define MENU_LINE_HEIGHT 20
#define MENU_LINE_MARGIN 20

static int	convert_color(int color);

static int	convert_color(int color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	a = (color >> 24) & 0xFF;
	if (a == 0)
		a = 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	draw_menu(t_app *data)
{
	int		i;
	t_coord	p0;
	t_coord	p1;
	int		bg_color;

	bg_color = convert_color(MENU_BG_COLOR);
	i = 0;
	while (i < SCREEN_L)
	{
		p0.x = 0;
		p0.y = i;
		p0.z = 0;
		p1.x = MENU_WIDTH;
		p1.y = i;
		p1.z = 0;
		draw_line(data->img, &p0, &p1, bg_color);
		i++;
	}
}

void	write_key_value(t_app *data, double x, double y, char *key, char *value)
{
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), key);
	print_str(data, x + 140, y, convert_color(MENU_VALUE_COLOR), value);
}

void	write_controls(t_app *data)
{
	double	x;
	double	y;

	x = MENU_LINE_MARGIN;
	y = 300;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), " ==== CONTROLS ==== ");
	y = y + MENU_LINE_HEIGHT;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), "ESC : CLOSE");
	y = y + MENU_LINE_HEIGHT;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), "RIGHT CLICK : MOVE");
	y = y + MENU_LINE_HEIGHT;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), "SCROLL : ZOOM IN/OUT");
	y = y + MENU_LINE_HEIGHT;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), "F : FIT MAP");
	y = y + MENU_LINE_HEIGHT;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), "J/K : -/+ Z_SCALE");
	y = y + MENU_LINE_HEIGHT;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), "H/L : -/+ XY_SCALE");
	y = y + MENU_LINE_HEIGHT;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), "ARROWS : -/+ XY_ROTATION");
	y = y + MENU_LINE_HEIGHT;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), "Q/E : -/+ Z_ROTATION");
}

void	write_map_info(t_app *data)
{
	double	x;
	double	y;
	char	*value;

	x = MENU_LINE_MARGIN;
	y = 100;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), " ==== MAP INFO ==== ");
	y = y + MENU_LINE_HEIGHT;
	write_key_value(data, x, y, "SIZE :", ft_itoa(data->map->size));
	y = y + MENU_LINE_HEIGHT;
	value = ft_itoa(data->map->width);
	write_key_value(data, x, y, "LENGTH(X) : ", value);
	free(value);
	y = y + MENU_LINE_HEIGHT;
	value = ft_itoa(data->map->length);
	write_key_value(data, x, y, "HEIGHT(Y) : ", value);
	free(value);
	y = y + MENU_LINE_HEIGHT;
	value = ft_itoa(data->map->max_depth);
	write_key_value(data, x, y, "+WIDTH(Z) : ", value);
	free(value);
	y = y + MENU_LINE_HEIGHT;
	value = ft_itoa(data->map->min_depth);
	write_key_value(data, x, y, "-WIDTH(Z) : ", value);
	free(value);
}

void	write_colorschemes(t_app *data)
{
	double	x;
	double	y;

	(void)data;
	x = MENU_LINE_MARGIN;
	y = 550;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), " ==== COLORSCHEMES ==== ");
	y = y + MENU_LINE_HEIGHT;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), "1 : DEFAULT");
	y = y + MENU_LINE_HEIGHT;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), "2 : NEON PURPLE");
	y = y + MENU_LINE_HEIGHT;
	print_str(data, x, y, convert_color(MENU_KEY_COLOR), "3 : HACKER GREEN");
}