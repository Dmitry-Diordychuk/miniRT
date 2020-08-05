/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_and_canvas.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 03:39:44 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/05 03:47:57 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "screen_and_canvas.h"

t_canvas	create_canvas(t_screen screen)
{
	return ((t_canvas){
				.left_border	= -screen.width / 2,
				.right_border	= screen.width / 2,
				.top_border	= screen.height / 2,
				.bottom_border	= -screen.height / 2,
				.width		= screen.width,
				.height		= screen.height
				});
}

/*
**	This function transform canvas point coordinates to screen coordinates
*/

t_point2d	canvas_to_screen(t_point2d canvas_point, t_screen screen)
{
	return ((t_point2d){
			.x = screen.width / 2 + canvas_point.x,
			.y = screen.height / 2 - canvas_point.y
			});
}

