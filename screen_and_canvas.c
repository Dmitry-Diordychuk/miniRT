/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_and_canvas.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 03:39:44 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 19:25:24 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "screen_and_canvas.h"

t_canvas	create_canvas(t_screen screen)
{
	return ((t_canvas){
				.left_border	= -screen.w / 2,
				.right_border	= screen.w / 2,
				.top_border	= screen.h / 2,
				.bottom_border	= -screen.h / 2,
				.width		= screen.w,
				.height		= screen.h
				});
}

/*
**	This function transform canvas point coordinates to screen coordinates
*/

t_point2d	canvas_to_screen(t_point2d canvas_point, t_screen screen)
{
	return ((t_point2d){
			.x = screen.w / 2 + canvas_point.x,
			.y = screen.h / 2 - canvas_point.y
			});
}
