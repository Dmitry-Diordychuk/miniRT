/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:38:02 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 01:20:25 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "square.h"

double	square_area(t_point3d v1, t_point3d v2, t_point3d v3, t_point3d v4)
{
	const double f1 = v1.x * v2.y - v1.y * v2.x;
	const double f2 = v2.x * v3.y - v2.y * v3.x;
	const double f3 = v3.x * v4.y - v3.y * v4.x;
	const double f4 = v4.x * v1.y - v4.y * v1.x;
	const double sum = fabs(f1 + f2 + f3 + f4);

	return (sum / 2);
}

int		choose_biggest_square(t_square square)
{
	int		result;
	double	areaxy;
	double	areaxz;
	double	areayz;

	areaxy = square_area((t_point3d){square.v1.x, square.v1.y, 0},
								(t_point3d){square.v2.x, square.v2.y, 0},
								(t_point3d){square.v3.x, square.v3.y, 0},
								(t_point3d){square.v4.x, square.v4.y, 0});
	areaxz = square_area((t_point3d){square.v1.x, square.v1.z, 0},
								(t_point3d){square.v2.x, square.v2.z, 0},
								(t_point3d){square.v3.x, square.v3.z, 0},
								(t_point3d){square.v4.x, square.v4.z, 0});
	areayz = square_area((t_point3d){square.v1.y, square.v1.z, 0},
								(t_point3d){square.v2.y, square.v2.z, 0},
								(t_point3d){square.v3.y, square.v3.z, 0},
								(t_point3d){square.v4.y, square.v4.z, 0});
	result = areaxy >= areaxz ? 1 : 2;
	if (result == 1)
		result = areaxy >= areayz ? 1 : 3;
	if (result == 2)
		result = areaxz >= areayz ? 2 : 3;
	return (result);
}

int		is_in_square(t_square square, t_point3d in_p)
{
	int chosen_plane;

	chosen_plane = choose_biggest_square(square);
	if (chosen_plane == 2)
	{
		in_p = (t_point3d){in_p.x, in_p.z, 0};
		square.v1 = (t_point3d){square.v1.x, square.v1.z, 0};
		square.v2 = (t_point3d){square.v2.x, square.v2.z, 0};
		square.v3 = (t_point3d){square.v3.x, square.v3.z, 0};
		square.v4 = (t_point3d){square.v4.x, square.v4.z, 0};
	}
	else if (chosen_plane == 3)
	{
		in_p = (t_point3d){in_p.y, in_p.z, 0};
		square.v1 = (t_point3d){square.v1.y, square.v1.z, 0};
		square.v2 = (t_point3d){square.v2.y, square.v2.z, 0};
		square.v3 = (t_point3d){square.v3.y, square.v3.z, 0};
		square.v4 = (t_point3d){square.v4.y, square.v4.z, 0};
	}
	if (angle_test(square, in_p))
		return (1);
	return (0);
}

double	intersect_square(t_ray3d r, void **obj)
{
	double		t;
	t_square	square;
	t_plane		plane;
	t_plane		*pointer;

	square = *(t_square*)*obj;
	plane = (t_plane){square.normal, square.center};
	pointer = &plane;
	t = intersect_plane(r, (void**)(&pointer));
	if (t >= 0 && is_in_square(square, ray_func(r, t)))
		return (t);
	return (-1);
}
