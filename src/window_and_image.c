/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:40:31 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/21 16:06:15 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_window		*create_window(void)
{
	t_window	*window;

	DO_IF(((window = (t_window*)malloc(sizeof(t_window))) == NULL),
			error_and_exit(error_mallocing, ""));
	window->colorscheme = 0;
	window->mlx_ptr = mlx_init();
	return (window);
}

static void		get_maxes(t_window *window, t_point ***array,
				double *max_x, double *max_y)
{
	int		x;
	int		y;

	*max_x = 0;
	*max_y = 0;
	x = 0;
	while (x < window->rows)
	{
		y = 0;
		while (y < window->cols)
		{
			if (array[x][y]->y > *max_y)
				*max_y = array[x][y]->y;
			if (array[x][y]->x > *max_x)
				*max_x = array[x][y]->x;
			y++;
		}
		x++;
	}
}

static double	get_scale(double width, double height)
{
	double	scale;

	scale = IDEAL_WINDOW_SIZE / ((width >= height) ? width : height);
	return ((scale > 1) ? scale : 1);
}

t_image			*create_image(t_window *window, t_point ***array)
{
	t_image	*img;
	double	max_width;
	double	max_height;

	DO_IF(((img = (t_image*)malloc(sizeof(t_image))) == NULL),
			error_and_exit(error_mallocing, ""));
	get_maxes(window, array, &max_width, &max_height);
	img->scale = get_scale(max_width, max_height);
	img->width = (max_width * img->scale + 0.5) + (MARGIN * 2);
	img->height = (max_height * img->scale + 0.5) + (MARGIN * 2);
	img->ptr = mlx_new_image(window->mlx_ptr, img->width, img->height);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->size_line, &img->endian);
	img->bpp /= 8;
	return (img);
}
