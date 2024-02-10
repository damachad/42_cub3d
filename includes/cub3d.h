
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
# define PLAYER_H 32 // necessary?
# define FOV 1 // in radians
# define NB_SPRITES 4

# define HEX_COLOR 0xFFFFFFFF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define GREEN_ALT 0x65B741
# define BLUE_LIGHT 0x7BD3EA
# define RED_BRICK 0xD04848

# define NO "textures/ice.png"
# define SO "textures/lava.png"
# define WE "textures/bricks.png"
# define EA "textures/leaves.png"
# define FLOOR "" // How to process input color ?
# define CEILING "" // Check for valid range
# define START_ANGLE 1 // angle in radians

# define PI 3.14159265358979323846
# define PI_DOUBLE 6.28318530717958647692
# define PI_HALF 1.57079632679489661923
# define PI_THREE_HALFS 4.71238898038468985769

// Structs

/* typedef enum s_dir{
	NO,
	SO,
	WE,
	EA
}			t_dir; */

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
	double	x;
	double	y;
}					t_point;

typedef struct s_point_int
{
	int	x;
	int	y;
}					t_point_int;

typedef struct s_map
{
	char			**bytes;
	unsigned int	rows;
}					t_map;

typedef struct s_sprite{
	void	*img;
	int		width;
	int		height;
}			t_sprite;

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
	int		floor[3];
	int		ceiling[3];
}				t_input;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	unsigned int	player_a;
	t_point			player_curr;
	double			time;
	double			old_time;
	t_map			*map;
	t_img			img;
	t_sprite		*sprites;
	t_input			*input;
}					t_game;

/*----------------------------map----------------------------*/
t_map	*new_map(unsigned int rows);
int		nr_lines(t_game *game, char *mapfile);
void	load_map(t_game *game, char *mapfile);

/*--------------------------checker--------------------------*/
void	validate_map(t_game *game);

/*---------------------------init----------------------------*/
void	init_graphics(t_game *game);
void	start_game(char	*mapfile);
void	load_sprites(t_game *game);

/*---------------------------clean---------------------------*/
void	error_msg(t_game *game, char *msg);
int		quit_prog(t_game *game);
void	destroy_game(t_game *game);
void	destroy_map(t_map *map);

/*--------------------------draw_line------------------------*/
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_game *game, t_point_int *a, t_point_int *b);

/*--------------------------background-----------------------*/
void	draw_background(t_img *img);
void	draw_wall_test(t_game *game);

/*--------------------------raycasting-----------------------*/
void	draw_wall(t_game *game);

/*----------------------------parser-------------------------*/
/* void	parse_file(t_game *game, char *file); */

/*----------------------------utils--------------------------*/
void	*safe_malloc(int bytes);

#endif
