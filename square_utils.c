/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 01:20:32 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/22 21:03:14 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "square.h"

int		get_quadrant(t_point3d v, t_point3d in_p)
{
	int quadrant;

	if (v.x > in_p.x)
	{
		quadrant = v.y > in_p.y ? 0 : 3;
		return (quadrant);
	}
	quadrant = v.y > in_p.y ? 1 : 2;
	return (quadrant);
}

double	x_intercept(t_point3d pt1, t_point3d pt2, double yy)
{
	return (pt2.x - ((pt2.y - yy) * ((pt1.x - pt2.x) / (pt1.y - pt2.y))));
}

void	adjust_delta(int *delta, t_point3d v1, t_point3d v2, t_point3d p_in)
{
	if (*delta == 3)
		*delta = -1;
	else if (*delta == -3)
		*delta = 1;
	else if (*delta == 2 || *delta == -2)
	{
		if (x_intercept(v1, v2, p_in.y) > p_in.x)
			*delta = -(*delta);
	}
}

int		angle_test(t_square square, t_point3d in_p)
{
	double		angle;
	int			delta;

	angle = 0;
	delta = get_quadrant(square.v2, in_p) - get_quadrant(square.v1, in_p);
	adjust_delta(&delta, square.v1, square.v2, in_p);
	angle += delta;
	delta = get_quadrant(square.v3, in_p) - get_quadrant(square.v2, in_p);
	adjust_delta(&delta, square.v2, square.v3, in_p);
	angle += delta;
	delta = get_quadrant(square.v4, in_p) - get_quadrant(square.v3, in_p);
	adjust_delta(&delta, square.v3, square.v4, in_p);
	angle += delta;
	delta = get_quadrant(square.v1, in_p) - get_quadrant(square.v4, in_p);
	adjust_delta(&delta, square.v4, square.v1, in_p);
	angle += delta;
	if (angle == 4 || angle == -4)
		return (1);
	return (0);
}
