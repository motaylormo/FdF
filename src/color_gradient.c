/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_gradient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:38:41 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/10 12:11:37 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_gradient	*make_gradient(int color1, int color2, int steps)
{
	t_gradient	*grad;

	RET_IF(((grad = (t_gradient*)malloc(sizeof(t_gradient))) == NULL), NULL);
	grad->curr_color = color1;
	grad->curr_red = (color1 & 0xFF0000) >> 16;
	grad->curr_green = (color1 & 0x00FF00) >> 8;
	grad->curr_blue = (color1 & 0x0000FF);
	grad->red_slope = (((color2 & 0xFF0000) - (color1 & 0xFF0000)) >> 16);
	grad->green_slope = (((color2 & 0x00FF00) - (color1 & 0x00FF00)) >> 8);
	grad->blue_slope = ((color2 & 0x0000FF) - (color1 & 0x0000FF));
	grad->red_slope = grad->red_slope / steps;
	grad->green_slope = grad->green_slope / steps;
	grad->blue_slope = grad->blue_slope / steps;
	return (grad);
}

void		free_gradient(t_gradient **grad)
{
	if (!grad)
		return ;
	free(*grad);
	*grad = NULL;
}

/*
** Iterates the current red, green, and blue by their respective slopes.
** Then turns these double values into ints
** (and no, just casting them wouldn't work)
** and stacks them together into a single color again.
*/

t_gradient	*iterate_color(t_gradient *grad)
{
	int red;
	int green;
	int blue;

	grad->curr_red += grad->red_slope;
	grad->curr_green += grad->green_slope;
	grad->curr_blue += grad->blue_slope;
	red = grad->curr_red + 0.5;
	green = grad->curr_green + 0.5;
	blue = grad->curr_blue + 0.5;
	grad->curr_color = (red << 16) + (green << 8) + (blue);
	return (grad);
}

/*
** Sort of like iterate_color
** Finds the color for a specific step along the gradient
*/

int			color_step(t_gradient *grad, int step)
{
	int red;
	int green;
	int blue;

	red = (grad->red_slope * step) + 0.5;
	green = (grad->green_slope * step) + 0.5;
	blue = (grad->blue_slope * step) + 0.5;
	return (grad->curr_color + (red << 16) + (green << 8) + (blue));
}
