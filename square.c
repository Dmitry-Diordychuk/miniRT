/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:21:28 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/04 23:00:39 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "square.h"

void	*create_square(t_point3d center, t_vector3d normal, double side)
{
	t_square			*s;
	double				half_side;
	t_matrix4d			m;
	const t_vector3d	prev_norm = (t_vector3d){0,0,-1};

	if (!(s = (t_square*)malloc(sizeof(t_square))))
		return (NULL);
	s->center = center;
	s->normal = normal;
	s->side = side;
	half_side = s->side / 2;
	s->v1 = (t_point3d){s->center.x - half_side, s->center.y + half_side, s->center.z};
	s->v2 = (t_point3d){s->center.x + half_side, s->center.y + half_side, s->center.z};
	s->v3 = (t_point3d){s->center.x + half_side, s->center.y - half_side, s->center.z};
	s->v4 = (t_point3d){s->center.x - half_side, s->center.y - half_side, s->center.z};
	m = get_i_mat4d();
	m = rotate_local(m, acos(dot_vec(prev_norm, s->normal)), normalize(cross_vec(prev_norm, s->normal)), s->center);
	s->normal = prev_norm;
	s->normal = v4_to_v3(mul_mat4d_vec4d(m, v3_to_v4(s->normal)));
	s->center = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(s->center)));
	s->v1 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(s->v1)));
	s->v2 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(s->v2)));
	s->v3 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(s->v3)));
	s->v4 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(s->v4)));
	return ((void*)s);
}

typedef	struct	s_point
{
	double x;
	double y;
}				t_point;


double	square_area(t_point3d v1, t_point3d v2, t_point3d v3, t_point3d v4)
{
	const double f1 = v1.x * v2.y - v1.y * v2.x;
	const double f2 = v2.x * v3.y - v2.y * v3.x;
	const double f3 = v3.x * v4.y - v3.y * v4.x;
	const double f4 = v4.x * v1.y - v4.y * v1.x;
	const double sum = fabs(f1 + f2 + f3 + f4);
	return (sum / 2);
}

int	choose_biggest_square(t_square square)
{
	const double areaxy = square_area((t_point3d){square.v1.x, square.v1.y, 0},
								(t_point3d){square.v2.x, square.v2.y, 0},
								(t_point3d){square.v3.x, square.v3.y, 0},
								(t_point3d){square.v4.x, square.v4.y, 0});
	const double areaxz = square_area((t_point3d){square.v1.x, square.v1.z, 0},
								(t_point3d){square.v2.x, square.v2.z, 0},
								(t_point3d){square.v3.x, square.v3.z, 0},
								(t_point3d){square.v4.x, square.v4.z, 0});
	const double areayz = square_area((t_point3d){square.v1.y, square.v1.z, 0},
								(t_point3d){square.v2.y, square.v2.z, 0},
								(t_point3d){square.v3.y, square.v3.z, 0},
								(t_point3d){square.v4.y, square.v4.z, 0});
	int result;

	result = areaxy >= areaxz ? 1 : 2;
	if (result == 1)
		result = areaxy >= areayz ? 1 : 3;
	if (result == 2)
		result = areaxz >= areayz ? 2 : 3;
	return (result);
}

int	get_quadrant(t_point3d v, t_point3d in_p)
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
	return (pt2.x -((pt2.y - yy) * ((pt1.x - pt2.x) / (pt1.y - pt2.y))));
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
// graphic gems 4
int	angle_test(t_square square, t_point3d in_p)
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

int	is_in_square(t_square square, t_point3d in_p)
{
	int chosen_plane;

	chosen_plane = choose_biggest_square(square);
	if (chosen_plane == 1)
	{
		if (angle_test(square, in_p))
			return (1);
	}
	else if (chosen_plane == 2)
	{
		in_p = (t_point3d){in_p.x, in_p.z, 0};
		square.v1 = (t_point3d){square.v1.x, square.v1.z, 0};
		square.v2 = (t_point3d){square.v2.x, square.v2.z, 0};
		square.v3 = (t_point3d){square.v3.x, square.v3.z, 0};
		square.v4 = (t_point3d){square.v4.x, square.v4.z, 0};
		if (angle_test(square, in_p))
			return (1);
	}
	else
	{
		in_p = (t_point3d){in_p.y, in_p.z, 0};
		square.v1 = (t_point3d){square.v1.y, square.v1.z, 0};
		square.v2 = (t_point3d){square.v2.y, square.v2.z, 0};
		square.v3 = (t_point3d){square.v3.y, square.v3.z, 0};
		square.v4 = (t_point3d){square.v4.y, square.v4.z, 0};
		if (angle_test(square, in_p))
			return (1);
	}
	return (0);
}

double	*intersect_square(t_ray3d r, void *obj)
{
	double		*t;
	t_square	square;
	t_plane		plane;

	square = *(t_square*)obj;
	plane = (t_plane){square.normal, square.center};
	if (!(t = intersect_plane(r, (void*)(&plane))))
		return (NULL);
	if (t[0] >= 0 && is_in_square(square, ray_param_func(r, t[0])))
		return(t);
	t[0] = -1;
	t[1] = -1;
	return (t);
}
