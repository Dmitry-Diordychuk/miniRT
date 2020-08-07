/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 03:02:10 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/07 03:15:40 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "point.h"
# include "screen_and_canvas.h"
# include "color.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_data;

void	draw_pixel(t_data *data, t_point2d p, int color);
void	draw_background(t_data *img, t_point2d point, t_screen screen,
							t_canvas canvas);

#endif
