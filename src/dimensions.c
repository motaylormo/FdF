/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 13:02:54 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/21 15:57:31 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_cols(char *line)
{
	int		cols;
	char	**split;

	cols = 0;
	RET_IF(!(split = ft_strsplit(line, ' ')), 0);
	while (split[cols])
	{
		free(split[cols]);
		cols++;
	}
	free(split);
	return (cols);
}

t_window	*count_rows_cols(t_window *window, char *filename)
{
	int		fd;
	char	*line;

	window->rows = 0;
	DO_IF((fd = open(filename, O_RDONLY)) < 0,
			error_and_exit(error_file_no_open, filename));
	while (get_next_line(fd, &line))
	{
		if (ft_strchr(line, ','))
			window->colorscheme = 1;
		if (window->rows == 0 && !(window->cols = count_cols(line)))
			error_and_exit(error_file_empty, filename);
		else if (count_cols(line) != window->cols)
			error_and_exit(error_map_error, filename);
		window->rows++;
		free(line);
	}
	close(fd);
	DO_IF(window->rows == 0, error_and_exit(error_file_empty, filename));
	return (window);
}
