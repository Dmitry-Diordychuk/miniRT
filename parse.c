/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:37:39 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 23:23:24 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_resolution(char *str, t_screen *screen)
{
	int			error;

	error = 0;
	str++;
	error += skip_spaces(&str);
	error += validate_int(str);
	screen->w = ft_atoi(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += validate_int(str);
	screen->h = ft_atoi(str);
	return (error);
}

int	parse_color(char *str, t_color3d *color)
{
	int	counter;

	if (skip_spaces(&str) != 0)
		return (-1);
	color->x = ft_atoi(str);
	counter = 0;
	counter += skip_count_digit(&str);
	if (*str != ',' || counter > 3 || counter == 0 ||
					color->x > 255 || color->x < 0)
		return (-1);
	str++;
	color->y = ft_atoi(str);
	counter = 0;
	counter += skip_count_digit(&str);
	if (*str != ',' || counter > 3 || counter == 0 ||
					color->y > 255 || color->y < 0)
		return (-1);
	str++;
	color->z = ft_atoi(str);
	counter = 0;
	counter += skip_count_digit(&str);
	if ((!ft_isspace(*str) && *str != '\0') || counter > 3 || counter == 0 ||
											color->z > 255 || color->z < 0)
		return (-1);
	return (0);
}

int	parse_ambient(char *str, t_light_environment *amb)
{
	int	error;

	error = 0;
	str++;
	error += skip_spaces(&str);
	amb->brightness = ft_atof(str);
	error += validate_double(&str);
	error += parse_color(str, &(amb->color));
	return (error);
}

int	parse_vector(char **str, t_vector3d *vector)
{
	if (skip_spaces(str) != 0)
		return (-1);
	vector->x = ft_atof(*str);
	skip_count_digit(&(*str));
	if (*(*str) == '.' && (*str)++)
		skip_count_digit(&(*str));
	if (*(*str) != ',')
		return (-1);
	(*str)++;
	vector->y = ft_atof(*str);
	skip_count_digit(&(*str));
	if (*(*str) == '.' && (*str)++)
		skip_count_digit(&(*str));
	if (*(*str) != ',')
		return (-1);
	(*str)++;
	vector->z = ft_atof(*str);
	skip_count_digit(&(*str));
	if (*(*str) == '.' && (*str)++)
		skip_count_digit(&(*str));
	if (!ft_isspace(*(*str)) && *(*str) != '\0')
		return (-1);
	return (0);
}

int	parse_file(t_vars *vars)
{
	int	i;
	int	error;
	int	r_flag;
	int	a_flag;

	error = 0;
	r_flag = 0;
	a_flag = 0;
	i = 0;
	while ((*vars).file_content[i] != NULL)
	{
		error = parse((*vars).file_content[i], &vars);
		if (error != 0)
			return (show_error(-1, "Error\nWrong input data!\n"));
		if ((*vars).file_content[i][0] == 'R')
			r_flag++;
		else if ((*vars).file_content[i][0] == 'A')
			a_flag++;
		if (r_flag > 1 || a_flag > 1)
			return (show_error(-1, "Error\nToo many A or R elements!\n"));
		i++;
	}
	return (0);
}
