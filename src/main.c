/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:12:41 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/21 16:03:44 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		display_image(t_window *window, t_image *img)
{
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, img->ptr,
			(window->width - img->width) / 2,
			(window->height - img->height) / 2);
	mlx_string_put(window->mlx_ptr, window->win_ptr, 10, 10, DEFAULT_COLOR,
			"Press \"I\" for isometric projection");
	mlx_string_put(window->mlx_ptr, window->win_ptr, 10, 30, DEFAULT_COLOR,
			"Press \"P\" for perspective projection");
	mlx_string_put(window->mlx_ptr, window->win_ptr, 10, 70, DEFAULT_COLOR,
			"Press \"ESC\" to exit program");
}

static int		handle_key(int key, t_window *window)
{
	if (key == ESC_KEY)
	{
		exit(0);
	}
	if (key == P_KEY || key == I_KEY)
	{
		mlx_clear_window(window->mlx_ptr, window->win_ptr);
		if (key == P_KEY)
			display_image(window, window->per_img);
		if (key == I_KEY)
			display_image(window, window->iso_img);
	}
	return (1);
}

static t_window	*fill_both_images(t_window *window, t_point ***array)
{
	array = set_iso_coords(window, array);
	window->iso_img = create_image(window, array);
	window->iso_img = draw_wireframe(window->iso_img, window, array);
	array = set_perspective_coords(window, array);
	window->per_img = create_image(window, array);
	window->per_img = draw_wireframe(window->per_img, window, array);
	window->width = (window->iso_img->width > window->per_img->width) ?
					window->iso_img->width : window->per_img->width;
	window->height = (window->iso_img->height > window->per_img->height) ?
						window->iso_img->height : window->per_img->height;
	window->width = (window->width < MIN_WIDTH) ? MIN_WIDTH : window->width;
	window->height = (window->height < MIN_HEIGHT) ? MIN_HEIGHT :
										window->height;
	return (window);
}

static void		fdf(char *filename)
{
	t_window	*window;
	t_point		***array;

	window = create_window();
	window = count_rows_cols(window, filename);
	array = get_array(window, filename);
	if (window->colorscheme == 0)
		array = add_color_scheme(window, array, get_color_scale(window, array));
	window = fill_both_images(window, array);
	window->win_ptr = mlx_new_window(window->mlx_ptr,
			window->width, window->height, WINDOW_TITLE);
	display_image(window, window->iso_img);
	mlx_key_hook(window->win_ptr, handle_key, window);
	mlx_loop(window->mlx_ptr);
}

int				main(int argc, char **argv)
{
	DO_IF(argc < 2, error_and_exit(error_no_arg, ""));
	if (argc > 2)
	{
		ft_putstr("You gave more than one argument, ");
		ft_putstr("so we're just going to use the first one: ");
		ft_putstr(argv[1]);
		ft_putstr("\n");
	}
	fdf(argv[1]);
	return (1);
}
