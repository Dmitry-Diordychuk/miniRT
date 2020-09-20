/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 17:10:22 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 19:20:47 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	to_trgb(t_color3d color)
{
	int t;

	t = 0;
	if (color.x > 255)
		color.x = 255;
	else if (color.x < 0)
		color.x = 0;
	if (color.y > 255)
		color.y = 255;
	else if (color.y < 0)
		color.y = 0;
	if (color.z > 255)
		color.z = 255;
	else if (color.z < 0)
		color.z = 0;
	return (t << 24 | (int)color.x << 16 | (int)color.y << 8 | (int)color.z);
}

int	create_trgb(int t, int r, int g, int b)
{
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	return (t << 24 | r << 16 | g << 8 | b);
}
