/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xy.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 17:38:48 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/09 17:38:58 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_xy	*xy(int x, int y, int color)
{
	t_xy	*xy;

	RET_IF(!(xy = (t_xy*)malloc(sizeof(t_xy))), NULL);
	xy->x = x;
	xy->y = y;
	xy->color = color;
	return (xy);
}

void	free_xy(t_xy **xy)
{
	if (!xy)
		return ;
	free(*xy);
	*xy = NULL;
}
