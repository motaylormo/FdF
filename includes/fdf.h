/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:21:44 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/21 16:07:01 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
** <fcntl.h> is for open
** <unistd.h> is for read, write, & close
** <stdlib.h> is for malloc, free, & exit
** <math.h> is allowed for fdf
** "mlx.h" and "libft.h" are for the miniLibX and libft libraries
*/
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../miniLibX/mlx.h"
# include "../libft/libft.h"

/*
** MACROS YOU MIGHT WANT TO CHANGE FOR DIFFERENT EFFECT
*/
# define WINDOW_TITLE "mtaylor fdf"
# define IDEAL_WINDOW_SIZE 1000
# define MARGIN 5
# define DEFAULT_COLOR 0xFFFFFF

# define HIGHS_COLOR 0xFF0000
# define LOWS_COLOR 0x0000FF
# define NEUT_COLOR 0x00FF00

/*
** The true isometric angle is 30 degrees (π/6 in radians)
** The angle for 2:1 (dimetric) is 26.57 degrees (0.46373398 in radians)
** The perspective angle was simply chosen so both images more or less align
*/
# define I_ANGLE (M_PI/6)
# define D_ANGLE 0.46373398
# define ANGLE D_ANGLE

# define PER_ANGLE M_PI/4

/*
** MACROS I CAN'T IMAGINE THERE WOULD EVER BE A REASON TO CHANGE
*/
# define RET_IF(cond, ret) if (cond) return (ret)
# define DO_IF(cond, task) if (cond) task

# define ESC_KEY 53
# define I_KEY 34
# define P_KEY 35

/*
** Make sure the window in big enough for the text
*/
# define MIN_WIDTH 380
# define MIN_HEIGHT 100

enum			e_errorcodes{
	error_no_arg,
	error_file_no_open,
	error_file_empty,
	error_map_error,
	error_mallocing
};

typedef struct	s_point
{
	int		alt;
	double	x;
	double	y;
	int		color;
}				t_point;

typedef struct	s_xy
{
	int		x;
	int		y;
	int		color;
}				t_xy;

typedef struct	s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	double		scale;
	int			width;
	int			height;
}				t_image;

typedef struct	s_window
{
	int		colorscheme;
	int		rows;
	int		cols;
	int		width;
	int		height;
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	*iso_img;
	t_image	*per_img;
}				t_window;

typedef struct	s_gradient
{
	double	red_slope;
	double	green_slope;
	double	blue_slope;
	double	curr_red;
	double	curr_green;
	double	curr_blue;
	int		curr_color;
}				t_gradient;

void			error_and_exit(int error, char *str);
t_window		*count_rows_cols(t_window *window, char *filename);
t_window		*create_window(void);
t_image			*create_image(t_window *window, t_point ***array);
t_point			***get_array(t_window *window, char *filename);
t_point			***add_color_scheme(t_window *window, t_point ***array,
					int color_scale);
int				get_color_scale(t_window *window, t_point ***array);
t_gradient		*make_gradient(int color1, int color2, int steps);
void			free_gradient(t_gradient **grad);
t_gradient		*iterate_color(t_gradient *grad);
int				color_step(t_gradient *grad, int step);
t_image			*put_line(t_image *img, t_xy *start, t_xy *end);
t_xy			*xy(int x, int y, int color);
void			free_xy(t_xy **xy);
t_point			***set_iso_coords(t_window *window, t_point ***array);
t_point			***set_perspective_coords(t_window *window, t_point ***array);
t_image			*draw_wireframe(t_image *img, t_window *window,
					t_point ***array);
t_point			***center(t_window *window, t_point ***array);

#endif
