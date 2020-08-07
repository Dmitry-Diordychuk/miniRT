/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_and_canvas.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 03:35:13 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/07 03:39:29 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_AND_CANVAS_H
# define SCREEN_AND_CANVAS_H

# include "point.h"

typedef struct		s_screen {
	const int	width;
	const int	height;
}			t_screen;

typedef struct		s_canvas {
	const int	left_border;
	const int	right_border;
	const int	top_border;
	const int	bottom_border;
	const int	width;
	const int	height;
}			t_canvas;

t_canvas		create_canvas(t_screen screen);
t_point2d		canvas_to_screen(t_point2d canvas_point,
							t_screen screen);

#endif

