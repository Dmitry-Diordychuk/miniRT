/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 03:03:04 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 01:55:42 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_pixel(t_data *data, t_point2d p, int color)
{
	char *dst;

	dst = data->addr +
	(p.y * data->line_length + p.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_background(t_data *img, t_point2d point, t_screen screen,
								t_canvas canvas)
{
	draw_pixel(img, canvas_to_screen(point, screen),
			create_trgb(0, 0, 200 - canvas.height / 5 + point.y / 5,
					255 - canvas.height / 5 + point.y / 5));
}
