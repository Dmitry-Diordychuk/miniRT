/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:39:12 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 16:10:10 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		skip_spaces(char **str)
{
	int counter;

	counter = 0;
	while (ft_isspace(**str))
	{
		(*str)++;
		counter++;
	}
	if (counter != 0)
		return (0);
	return (-1);
}

int		skip_count_digit(char **str)
{
	int counter;

	counter = 0;
	if (**str == '-')
		(*str)++;
	while (ft_isdigit(**str))
	{
		(*str)++;
		counter++;
	}
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			(*str)++;
			counter++;
		}
	}
	return (counter);
}

int		parse(char *line, t_vars **vars)
{
	if (line[0] == 'R')
		return (parse_resolution(line, &(*vars)->screen));
	else if (line[0] == 'A')
		return (parse_ambient(line, &((*vars)->scene.ambient)));
	else if (line[0] == 'c' && ft_isspace(line[1]))
	{
		(*vars)->scene.cameras_counter++;
		return (parse_camera(line, &((*vars)->scene.cameras)));
	}
	else if (line[0] == 'l')
		return (parse_light(line, &((*vars)->scene.lights)));
	else if (line[0] == 's' && line[1] == 'p')
		return (parse_sphere(line, &((*vars)->scene.objects)));
	else if (line[0] == 'p' && line[1] == 'l')
		return (parse_plane(line, &((*vars)->scene.objects)));
	else if (line[0] == 's' && line[1] == 'q')
		return (parse_square(line, &((*vars)->scene.objects)));
	else if (line[0] == 'c' && line[1] == 'y')
		return (parse_cylinder(line, &((*vars)->scene.objects)));
	else if (line[0] == 't' && line[1] == 'r')
		return (parse_triangle(line, &((*vars)->scene.objects)));
	return (0);
}
