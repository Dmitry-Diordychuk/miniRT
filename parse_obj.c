/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:45:06 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 02:46:00 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_sphere(char *str, t_list **objects)
{
	t_sphere	sphere;
	void		*new;
	t_color3d	color;
	int			error;
	t_list		*new_elem;

	error = 0;
	str += 2;
	error += skip_spaces(&str);
	error += parse_vector(str, &(sphere.position));
	skip_vector(&str);
	error += skip_spaces(&str);
	sphere.radius = ft_atof(str) / 2;
	error += validate_double(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &color);
	if (!(new = create_sphere(sphere.position, sphere.radius)))                  //malloc free
		return (-1);
	if (!(new = create_object("Sphere", new, color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new)))
		return (-1);
	ft_lstpush(objects, new_elem);
	return (error);
}

int	parse_plane(char *str, t_list **objects)
{
	t_plane		plane;
	void		*new;
	t_list		*new_elem;
	t_color3d	color;
	int			error;

	error = 0;
	str += 2;
	error += skip_spaces(&str);
	error += parse_vector(str, &(plane.q));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(plane.normal));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &color);
	if (!(new = create_plane(plane.q, plane.normal)))
		return (-1);
	if (!(new = create_object("Plane", new, color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new)))
		return (-1);
	ft_lstpush(objects, new_elem);
	return (error);
}

int	parse_square(char *str, t_list **objects)
{
	t_square	square;
	void		*new;
	t_list		*new_elem;
	t_color3d	color;
	int			error;

	error = 0;
	str += 2;
	error += skip_spaces(&str);
	error += parse_vector(str, &(square.center));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(square.normal));
	skip_vector(&str);
	error += skip_spaces(&str);
	square.side = ft_atof(str);
	error += validate_double(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &color);
	if (!(new = create_square(square.center, square.normal, square.side)))
		return (-1);
	if (!(new = create_object("Square", new, color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new)))
		return (-1);
	ft_lstpush(objects, new_elem);
	return (error);
}

int	parse_cylinder(char *str, t_list **objects)
{
	t_cylinder	cylinder;
	void		*new;
	t_list		*new_elem;
	t_color3d	color;
	int			error;

	error = 0;
	str += 2;
	error += skip_spaces(&str);
	error += parse_vector(str, &(cylinder.position));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(cylinder.direction));
	skip_vector(&str);
	error += skip_spaces(&str);
	cylinder.d = ft_atof(str);
	error += validate_double(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	cylinder.h = ft_atof(str);
	error += validate_double(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &color);
	if (!(new = create_cylinder(cylinder.position, cylinder.direction, cylinder.d, cylinder.h)))
		return (-1);
	if (!(new = create_object("Cylinder", new, color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new)))
		return (-1);
	ft_lstpush(objects, new_elem);
	return (error);
}

int	parse_triangle(char *str, t_list **objects)
{
	t_triangle	triangle;
	void		*new;
	t_list		*new_elem;
	t_color3d	color;
	int			error;

	error = 0;
	str += 2;
	error += skip_spaces(&str);
	error += parse_vector(str, &(triangle.v1));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(triangle.v2));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(triangle.v3));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &color);
	if (!(new = create_triangle(triangle.v1, triangle.v2, triangle.v3)))
		return (-1);
	if (!(new = create_object("Triangle", new, color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new)))
		return (-1);
	ft_lstpush(objects, new_elem);
	return (error);
}
