/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:05:59 by lfarias-          #+#    #+#             */
/*   Updated: 2022/11/03 19:12:20 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"

# define SCREEN_W 1920
# define SCREEN_L 1080

# define MENU_WIDTH 280
# define MENU_BG_COLOR 0x002E323C
# define MENU_KEY_COLOR 0x00AFB0AF
# define MENU_VALUE_COLOR 0x00FF6188
# define CANVAS_MARGIN 30

// window management define
# define KEY_PRESS 2
# define CLOSE_WIN 17

// options bindings
# define ESC_KEY 53
# define F_KEY 3

// J/K -/+ z_scale
# define K_KEY 40
# define J_KEY 38

// H/L -/+ xy_scale
# define H_KEY 4
# define L_KEY 37

typedef struct s_coord
{
	double			x;
	double			y;
	double			z;
	int				color;
}	t_coord;

typedef struct s_map
{
	char			*name;
	int				width;
	int				length;
	int				size;
	int				max_depth;
	int				min_depth;
	double			scale;
	double			z_scale;
	t_coord			source;
	struct s_coord	*points;
}	t_map;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_frame;

typedef struct s_app_info
{
	void	*mlx;
	void	*window;
	t_frame	*bitmap;
	t_coord	*projection;
	t_map	*map;
	int		win_close;
	int		map_draw;
	int		fit;
}	t_app;

// app
void	app_run(t_app *app_data);
int		mlx_load(t_app *app_data);
void	vars_load(t_app *app_data, int argc, char **argv);
int		check_input_size(int argc);
double	get_z_scale(int argc, char **argv);
double	get_scale(int map_width, int map_length, int argc, char **argv);
void	all_you_need_is_kill(t_app *app_data);

// events & controls
int		render_scene(t_app *app_data);
int		key_press(int keycode, void *param);
int		close_button(void *param);

// map
t_map	*map_get(char *map_name);
int		get_line_size(char **fields);
void	get_minmax_z(t_map *map);
int		check_line_format(char **fields);
void	erase_lines(t_list *map_line);

//draw
void	mlx_pixel_put_v2(t_frame *frame, int x, int y, int color);
void	draw_line(t_frame *img, t_coord *point0, t_coord *point1, int color);
void	draw_map(t_app *data, t_coord *projection);
void	draw_menu(t_app *data);
void	render_img(t_app *data, t_coord *projection);
void	fit_img(t_app *data, t_coord *projection);
void	clear_img(t_app *data, t_coord *projection);
int		out_of_screen(t_coord *p0, t_coord *p1);
int		on_screen(double x, double y);
void	free_img_buffer(t_app *app_data, t_frame *screen);
void	display_img(t_app *app_data);

// math
double	dg2_rad(double angle);
int		round_to_i(double value);

// transformations
void	isometric(t_coord *points, int size);
void	scale(t_coord *points, double scale, int size);
void	translate(t_coord *point, t_coord *move, int size);
void	z_scale(t_coord *projection, double z_scale, int size);

//utils
void	write_map_info(t_app *data);
void	write_controls(t_app *data);
void	print_str(t_app *data, t_coord *point, int color, char *value);
void	free_2d_array(void **matrix);
t_coord	*copy_points(t_coord *dst, t_coord *src, int size);
int		atohex(char *str);

//error
void	print_err_msg(char *err_msg);
#endif
