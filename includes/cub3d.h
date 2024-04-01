/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:53:36 by damachad          #+#    #+#             */
/*   Updated: 2024/02/09 15:17:01 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdbool.h>

/*--------------------Macros--------------------*/
# define SCREEN_WIDTH 960
# define SCREEN_HEIGHT 768
# define CUB_SIDE 64
# define FOV 1
# define NB_SPRITES 4

# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define GREEN_ALT 0x65B741
# define BLUE_LIGHT 0x7BD3EA
# define RED_BRICK 0xD04848

# define START_ANGLE 1
# define MINIMAP_SCALE 3.0
# define SPEED 1.8
# define ROT_SPEED 0.02
# define WALL_BUFF 10
# define SLIDE_BUFF 0.17

# define PI 3.1415926535
# define PI_DOUBLE 6.2831853071
# define PI_HALF 1.5707963267
# define PI_THREE_HALFS 4.7123889803

/*--------------------Structs--------------------*/
typedef enum s_dir
{
	N,
	S,
	E,
	W
}			t_dir;

typedef enum s_color_type
{
	FLOOR,
	CEILING
}			t_color_type;

/* line drawing algorithm variables */
typedef struct s_bresenham
{
	int	x0;
	int	y0;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}		t_bresenham;

typedef struct s_point
{
	float	x;
	float	y;
}					t_point;

typedef struct s_point_int
{
	int	x;
	int	y;
}					t_point_int;

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
	int	color;
}				t_square;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	l_a;
	bool	r_a;
}			t_keys;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_input
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f_color;
	int		c_color;
}				t_input;

typedef struct s_calc
{
	t_point	a;
	t_point	b;
	t_point	offset;
	bool	set;
}			t_calc;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	float			p_angle;
	float			p_b_angle;
	t_point			p_pos;
	t_point			p_dir;
	char			**map;
	char			*line;
	char			*line_tmp;
	int				map_cols;
	int				map_rows;
	size_t			l_top;
	size_t			l_bottom;
	size_t			l_left;
	size_t			l_right;
	bool			player;
	t_img			img;
	t_img			*sprites;
	t_input			*input;
	t_keys			keys;
	t_calc			*calc;
	int				wall_side;
	int				back_wall;
	float			d_proj_plane;
	float			alpha;
	float			draw_offset_x;
	float			draw_offset_y;
	t_img			*right_texture;
}					t_game;

/*---------------------------init----------------------------*/
void	start_game(char	*mapfile);
void	init_input(t_input *input);
void	init_player(t_game *g);
void	init_graphics(t_game *game);
void	load_sprites(t_game *game);
t_img	new_img(t_game *game);

/*---------------------------clean---------------------------*/
void	error_msg(t_game *game, char *msg);
int		quit_prog(t_game *game);
void	destroy_game(t_game *game);

/*--------------------------draw_line------------------------*/
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, t_point_int *a, t_point_int *b, int color);

/*---------------------------textures------------------------*/
void	draw_background(t_game *game);
void	draw_column(t_game *g, int x, float y_btm, float wall_h);

/*--------------------------raycasting-----------------------*/
float	wall_dist_horiz(t_game *g, t_point p, float alpha, bool set);
float	wall_dist_vertical(t_game *g, t_point p, float alpha, bool set);

/*--------------------------raycast_utils-----------------------*/
bool	is_wall(t_game *g, int x, int y);
float	get_xa(float alpha);
float	get_ya(float alpha);
void	set_texture(t_game *g, bool horiz);
void	set_wall_side(t_game *g, float horizontal, float vertical);

/*---------------------------draw_wall------------------------*/
int		draw_wall(t_game *game);

/*----------------------------parser-------------------------*/
void	parse_file(t_game *game, char *file);
void	parse_color(t_game *game, char *line, t_color_type color_type);
void	parse_texture(t_game *game, char *line, t_dir dir);
void	parse_map(t_game *game, char *file);
void	get_map_size(t_game *game, char *line);
bool	is_empty_line(char *line);
void	free_line_end_game(t_game *game, char *line, char *msg);
void	check_map(t_game *game);
void	get_map_limits(t_game *game);
void	free_partial_map(t_game *game, int rows_allocated);
bool	is_valid_char(t_game *game, char c);
void	set_player(t_game *game, char c, int x, int y);
void	get_map_size(t_game *game, char *line);
void	*safe_malloc(int bytes);

/*----------------------------utils--------------------------*/
bool	facing_up(float angle);
bool	facing_down(float angle);
bool	facing_left(float angle, float buffer);
bool	facing_right(float angle, float buffer);
float	set_angle(float angle);

/*---------------------------movement------------------------*/
void	rotate(t_game *g);
void	sideways_movement(t_game *g);
void	front_back_move(t_game *g);

/*---------------------------move_utils------------------------*/
bool	is_empty_corner(t_game *g, float dir_x, float dir_y, float angle);
int		handle_keypress(int keysym, t_game *g);
int		handle_keyrelease(int keysym, t_game *g);
int		render_movement(t_game *g);

/* -----------------------debug print----------------------- */
void	print_input(t_input *input);
void	print_map(t_game *game);

#endif
