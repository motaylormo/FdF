/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:14:42 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/21 16:06:35 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	*create_point(char *str, int colorscheme)
{
	t_point	*point;

	DO_IF(!(point = (t_point*)malloc(sizeof(t_point))),
			error_and_exit(error_mallocing, ""));
	point->alt = ft_atoi(str);
	if (colorscheme == 1)
	{
		point->color = DEFAULT_COLOR;
		while (*str && *str != ' ')
		{
			if (*str == ',')
			{
				str += 3;
				point->color = ft_atoibase(str, 16);
			}
			str++;
		}
	}
	return (point);
}

static t_point	***malloc_array(int rows, int cols)
{
	t_point	***array;
	int		i;

	i = 0;
	RET_IF(!(array = (t_point***)malloc(rows * sizeof(t_point**))), NULL);
	while (i < rows)
	{
		RET_IF(!(array[i] = (t_point**)malloc(cols * sizeof(t_point*))), NULL);
		i++;
	}
	return (array);
}

static t_point	**read_line(t_window *window, t_point **array_row, char *line)
{
	int y;

	y = 0;
	while (y < window->cols)
	{
		while (*line && (*line == ' ' || *line == '\n'))
			line++;
		array_row[y] = create_point(line, window->colorscheme);
		while (*line && *line != ' ')
			line++;
		y++;
	}
	return (array_row);
}

static t_point	***fill_array(t_window *window, t_point ***array,
				char *filename)
{
	char	*line;
	int		fd;
	int		x;

	DO_IF((fd = open(filename, O_RDONLY)) < 0,
			error_and_exit(error_file_no_open, filename));
	x = 0;
	while (x < window->rows)
	{
		get_next_line(fd, &line);
		array[x] = read_line(window, array[x], line);
		free(line);
		x++;
	}
	close(fd);
	return (array);
}

t_point			***get_array(t_window *window, char *filename)
{
	t_point	***array;

	DO_IF(!(array = malloc_array(window->rows, window->cols)),
			error_and_exit(error_mallocing, ""));
	array = fill_array(window, array, filename);
	return (array);
}
