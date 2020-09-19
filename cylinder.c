/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 19:53:14 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/19 22:35:29 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

t_vector3d	normal;

t_vector3d	calculate_cylinder_normal(t_cylinder cylinder, t_point3d int_point)
{
	return (normal);
}

void	*create_cylinder(t_point3d position, t_vector3d direction, double d, double h)
{
	t_cylinder *cylinder;

	cylinder = (t_cylinder*)malloc(sizeof(t_cylinder));
	cylinder->position = position;
	cylinder->direction = normalize(direction);
	cylinder->d = d;
	cylinder->h = h;
	return ((void*)cylinder);
}

int	sign(double n)
{
	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);
	return (1);
}

double	is_point_between(t_cylinder cylinder, t_ray3d r, t_vector3d b, double t)
{
	t_point3d	inter_point;
	double		s1;
	double		s2;

	inter_point = ray_func(r, t);
	s1 =
	fabs(dot_v(sub_v(cylinder.position, inter_point), cylinder.direction))
											/ module_v(cylinder.direction);
	s2 =
	fabs(dot_v(sub_v(b, inter_point), cylinder.direction))
											/ module_v(cylinder.direction);
	if (!(fabs(s1) < fabs(cylinder.h) && sign(s1) == sign(cylinder.h)
	&& fabs(s2) < fabs(cylinder.h) && sign(s2) == sign(cylinder.h)))
		return (-1);
	return (t);
}

int	choose_closest_point(double *t)
{
	int	comp_1;
	int comp_2;
	int result;

	if (t[0] < 0)
		comp_1 = t[1] < 0 ? -1 : 1;
	else if (t[1] < 0)
		comp_1 = 0;
	else
		comp_1 = t[0] < t[1] ? 0 : 1;
	if (t[2] < 0)
		comp_2 = t[3] < 0 ? -1 : 3;
	else if (t[3] < 0)
		comp_2 = 2;
	else
		comp_2 = t[2] < t[3] ? 2 : 3;
	if (comp_1 == -1)
		return (comp_2 == -1 ? -1 : comp_2);
	else if (comp_2 == -1)
		return (comp_1);
	return (t[comp_1] < t[comp_2] ? comp_1 : comp_2);
}

double	intersect_cylinder(t_ray3d r, void *obj)
{
	t_cylinder	c;
	double		t[4];
	double		d;
	t_vector3d	v[3];

	c = *(t_cylinder*)obj;
	v[0] = normalize(cross_v(r.direction, c.direction));
	v[1] = sub_v(r.origin, c.position);
	d = fabs(dot_v(v[1], v[0]));
	v[2] = sum_v(c.position, mul_vs(c.direction, c.h));
	//if (d > c.diameter / 2)
	//	return (-1);
	v[1] = cross_v(v[1], c.direction);
	t[2] = -dot_v(v[1], v[0]) / module_v(cross_v(r.direction, c.direction));
	v[1] = normalize(cross_v(v[0], c.direction));
	t[3] = sqrt(pow(c.d/2, 2) - d * d) / dot_v(r.direction, v[1]);
	t[0] = is_point_between(c, r, v[2], t[2] - t[3]);
	t[1] = is_point_between(c, r, v[2], t[2] + t[3]);
	t[2] = intersect_plane(r, &(t_plane){normalize(c.direction), c.position});
	t[3] = intersect_plane(r, &(t_plane){normalize(c.direction), v[2]});
	if (t[2] >= 0 && module_v(sub_v(ray_func(r, t[2]), c.position)) > c.d / 2)
			t[2] = -1;
	if (t[3] >= 0 && module_v(sub_v(ray_func(r, t[3]), v[2])) > c.d / 2)
			t[3] = -1;
	int closest_t = choose_closest_point(t);
	if (closest_t == 0 || closest_t == 1)
		normal = normal_to_camera(div_vs(sub_v(sub_v(ray_func(r, t[closest_t]),
		c.position), mul_vs(c.direction, dot_v(sub_v(ray_func(r, t[closest_t]),
		c.position), c.direction))), c.d/2), r.direction);
	else if (closest_t == 2 || closest_t == 3)
		normal = normal_to_camera(c.direction, r.direction);
	return (closest_t != -1 ? t[closest_t] : -1);
}
