
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

// Macros
# define SCREEN_WIDTH 960
# define SCREEN_HEIGHT 768
# define CUB_SIDE 64
# define FOV 1 // in radians
# define NB_SPRITES 4

# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define GREEN_ALT 0x65B741
# define BLUE_LIGHT 0x7BD3EA
# define RED_BRICK 0xD04848

/* # define NORTH "textures/directions/N1.xpm"
# define SOUTH "textures/directions/S1.xpm"
# define EAST "textures/directions/E1.xpm"
# define WEST "textures/directions/W1.xpm" */
# define START_ANGLE 1 // angle in radians
# define MINIMAP_SCALE 3.0
# define SPEED 2
# define ROT_SPEED 0.04
# define WALL_BUFF 6
# define SLIDE_BUFF 0.17

// east is 0
# define PI 3.1415926535 // west
# define PI_DOUBLE 6.2831853071
# define PI_HALF 1.5707963267 // north
# define PI_THREE_HALFS 4.7123889803 // south

// Structs

typedef enum s_dir{
	N,
	S,
	E,
	W
}			t_dir;

typedef enum s_color_type{
	FLOOR,
	CEILING
}			t_color_type;

//line drawing algorithm variables
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

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	l_a;
	bool	r_a;
}			t_keys;

typedef struct s_img {
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
	int		floor_color;
	int		ceiling_color;
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
	t_point			p_pos;
	t_point			p_dir;
	char			**map;
	int				map_cols;
	int				map_rows;
	bool			player;
	t_img			img;
	t_img			*sprites; 
	t_input			*input;
	t_keys			keys;
	t_calc			*calc;
	int				wall_side;
	int				back_wall;
	float			minimap_scale;
	float			alpha;
	float			draw_offset_x;
	float			draw_offset_y;
	t_img			*right_texture;
}					t_game;

/*---------------------------init----------------------------*/
void	init_graphics(t_game *game);
void	start_game(char	*mapfile);
void	load_sprites(t_game *game);
t_img	new_img(t_game *game);

/*---------------------------clean---------------------------*/
void	error_msg(t_game *game, char *msg);
int		quit_prog(t_game *game);
void	destroy_game(t_game *game);
/* void	destroy_map(t_map *map); */

/*--------------------------draw_line------------------------*/
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_game *game, t_point_int *a, t_point_int *b, int color);

/*---------------------------textures------------------------*/
void	draw_background(t_game *game);
void	draw_column(t_game *g, int x, float y_btm, float wall_h);

// void	draw_wall_test(t_game *game);

/*--------------------------raycasting-----------------------*/
int		draw_wall(t_game *game);
bool	is_wall(t_game *g, int x, int y);

/*----------------------------parser-------------------------*/
void	parse_file(t_game *game, char *file);
void	parse_color(t_game *game, char *line, t_color_type color_type);
void	parse_texture(t_game *game, char *line, t_dir dir);
void	parse_map(t_game *game, char *file);
void	get_map_size(t_game *game, char *line);
bool	is_empty_line(char *line);
void	check_map(t_game *game);

/*----------------------------utils--------------------------*/
void	*safe_malloc(int bytes);
bool	facing_up(float angle);
bool	facing_down(float angle);
bool	facing_left(float angle, float buffer);
bool	facing_right(float angle, float buffer);

/*---------------------------movement------------------------*/
int		handle_keypress(int keysym, t_game *g);
int		handle_keyrelease(int keysym, t_game *g);
int		render_movement(t_game *g);

/*---------------------------minimap------------------------*/
void	draw_minimap(t_game *g);

/* -----------------------debug print----------------------- */
void	print_input(t_input *input);
void	print_map(t_game *game);

#endif
