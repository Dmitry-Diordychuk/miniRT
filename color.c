/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 17:10:22 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/11 18:37:34 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	color3d_to_trgb(t_color3d color)
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

int	get_t(unsigned int trgb)
{
	return (((0xff << 24) & trgb) >> 24);
}

int	get_r(unsigned int trgb)
{
	return (((0xff << 16) & trgb) >> 16);
}

int	get_g(unsigned int trgb)
{
	return (((0xff << 8) & trgb) >> 8);
}

int	get_b(unsigned int trgb)
{
	return (0xff & trgb);
}
