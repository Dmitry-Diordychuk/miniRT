/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_and_canvas.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 03:35:13 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/05 03:48:10 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

typedef struct	s_point2d {
	int	x;
	int	y;
}		t_point2d;

typedef struct		s_screen {
	const int	width;
	const int	height;
	const int	aspect_ratio;
}			t_screen;

typedef struct		s_canvas {
	const int	left_border;
	const int	right_border;
	const int	top_border;
	const int	bottom_border;
	const int	width;
	const int	height;
}			t_canvas;

t_canvas	create_canvas(t_screen screen);
t_point2d	canvas_to_screen(t_point2d canvas_point, t_screen screen);

#endif
