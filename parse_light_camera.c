/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:46:48 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 02:46:56 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_camera(char *str, t_list **cameras)
{
	t_camera	c;
	void		*new_camera;
	int			error;
	t_list		*new_elem;

	error = 0;
	str++;
	error += skip_spaces(&str);
	error += parse_vector(str, &(c.ray.origin));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(c.direction));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += validate_double(str);
	c.fov = ft_atoi(str);
	if (!(new_camera = create_camera(c.ray.origin, c.direction, c.fov)))
		return (error - 1);
	if (!(new_elem = ft_lstnew(new_camera)))
	{
		free(new_camera);
		return (error - 1);
	}
	ft_lstpush(cameras, new_elem);
	return (error);
}

int	parse_light(char *str, t_list **lights)
{
	t_light_point	light;
	void			*new_light;
	t_list			*new_elem;
	int				error;

	error = 0;
	str++;
	error += skip_spaces(&str);
	error += parse_vector(str, &(light.position));
	skip_vector(&str);
	error += skip_spaces(&str);
	light.brightness = ft_atof(str);
	error += validate_double(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &(light.color));
	if (!(new_light = create_light_point(light.position, light.brightness, light.color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new_light)))
		return (-1);
	ft_lstpush(lights, new_elem);
	return (error);
}
