/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :::      ::::::::   */
/*                                                    :::      ::::::::   */
/*   By: lfarias- <lfarias-@student.42.rio>         :::   :::   :::        */
/*                                                https://github.com/lfariasr */
/*                                                    https://42.rio         */
/*   Created: 2022/09/23 19:05:59 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/17 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "MLX42/MLX42.h"

# define SCREEN_W 1920
# define SCREEN_L 1080

# define MENU_WIDTH 280
# define MENU_BG_COLOR 0x002E323C
# define MENU_KEY_COLOR 0x00AFB0AF
# define MENU_VALUE_COLOR 0x00FF6188
# define CANVAS_MARGIN 30

// options bindings
# define ESC_KEY MLX_KEY_ESCAPE
# define F_KEY MLX_KEY_F
# define K_KEY MLX_KEY_K
# define J_KEY MLX_KEY_J
# define H_KEY MLX_KEY_H
# define L_KEY MLX_KEY_L

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

typedef struct s_app_info
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*str_img[20];
	int				str_count;
	t_coord			*projection;
	t_map			*map;
	int				map_draw;
	int				fit;
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
void	render_loop(void *param);
void	key_handler(mlx_key_data_t keydata, void *param);
void	close_handler(void *param);

// map
t_map	*map_get(char *map_name);
int		get_line_size(char **fields);
void	get_minmax_z(t_map *map);
int		check_line_format(char **fields);
void	erase_lines(t_list *map_line);

//draw
void	draw_line(mlx_image_t *img, t_coord *point0, t_coord *point1, uint32_t color);
void	draw_map(t_app *data, t_coord *projection);
void	draw_menu(t_app *data);
void	render_img(t_app *data, t_coord *projection);
void	fit_img(t_app *data, t_coord *projection);
void	clear_img(mlx_image_t *img);
void	display_img(t_app *app_data);
int		out_of_screen(t_coord *p0, t_coord *p1);
int		on_screen(double x, double y);

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
void	print_str(t_app *data, double x, double y, int color, char *value);
void	free_2d_array(void **matrix);
t_coord	*copy_points(t_coord *dst, t_coord *src, int size);
int		atohex(char *str);

//error
void	print_err_msg(char *err_msg);
#endif