/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:04:19 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/21 14:23:45 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_and_exit(int error, char *str)
{
	if (error == error_no_arg)
		ft_putendl("We need an argument, a file to read.");
	if (error == error_file_no_open || error == error_file_empty
			|| error == error_map_error)
	{
		ft_putstr("The file ");
		ft_putstr(str);
		if (error == error_file_no_open)
		{
			ft_putstr(" could not be opened. Either it does not exist, ");
			ft_putendl("or you don't have the rights to open it.");
		}
		if (error == error_file_empty)
			ft_putendl(" is empty.");
		if (error == error_map_error)
			ft_putendl(" contains a line length error.");
	}
	if (error == error_mallocing)
		ft_putendl("Could not malloc the space needed.");
	exit(1);
}
