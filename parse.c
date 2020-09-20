/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:37:39 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 02:46:43 by kdustin          ###   ########.fr       */
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
	screen->width = ft_atoi(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += validate_int(str);
	screen->height = ft_atoi(str);
	return (error);
}

int	parse_color(char *str, t_color3d *color)
{
	int	counter;

	color->x = ft_atoi(str);
	counter = 0;
	counter += skip_count_digit(&str);
	if (*str != ',' || counter > 3 || counter == 0 || color->x > 255 || color->x < 0)
		return (-1);
	str++;
	color->y = ft_atoi(str);
	counter = 0;
	counter += skip_count_digit(&str);
	if (*str != ',' || counter > 3 || counter == 0 || color->y > 255 || color->y < 0)
		return (-1);
	str++;
	color->z = ft_atoi(str);
	counter = 0;
	counter += skip_count_digit(&str);
	if ((!ft_isspace(*str) && *str != '\0') || counter > 3 || counter == 0 || color->z > 255 || color->z < 0)
		return (-1);
	return (0);
}

int	parse_ambient(char *str, t_light_environment *amb)
{
	int	error;

	error = 0;
	str++;
	error += skip_spaces(&str);
	error += validate_double(str);
	amb->brightness = ft_atof(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &(amb->color));
	return (error);
}

int	parse_vector(char *str, t_vector3d *vector)
{
	vector->x = ft_atof(str);
	skip_count_digit(&str);
	if (*str == '.' && str++)
		skip_count_digit(&str);
	if (*str != ',')
		return (-1);
	str++;
	vector->y = ft_atof(str);
	skip_count_digit(&str);
	if (*str == '.' && str++)
		skip_count_digit(&str);
	if (*str != ',')
		return (-1);
	str++;
	vector->z = ft_atof(str);
	skip_count_digit(&str);
	if (*str == '.' && str++)
		skip_count_digit(&str);
	if (!ft_isspace(*str) && *str != '\0')
		return (-1);
	return (0);
}

int	parse_file(char **file_content, t_vars *vars)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (file_content[i] != NULL)
	{
		if (file_content[i][0] == 'R')
			error += parse_resolution(file_content[i], &vars->screen);
		else if (file_content[i][0] == 'A')
			error += parse_ambient(file_content[i], &(vars->scene.environment_light));
		else if (file_content[i][0] == 'c' && ft_isspace(file_content[i][1]))
		{
			error += parse_camera(file_content[i], &(vars->scene.cameras));
			vars->scene.cameras_counter++;
		}
		else if (file_content[i][0] == 'l')
			error += parse_light(file_content[i], &(vars->scene.lights));
		else if (file_content[i][0] == 's' && file_content[i][1] == 'p')
			error += parse_sphere(file_content[i], &(vars->scene.objects));
		else if (file_content[i][0] == 'p' && file_content[i][1] == 'l')
			error += parse_plane(file_content[i], &(vars->scene.objects));
		else if (file_content[i][0] == 's' && file_content[i][1] == 'q')
			error += parse_square(file_content[i], &(vars->scene.objects));
		else if (file_content[i][0] == 'c' && file_content[i][1] == 'y')
			error += parse_cylinder(file_content[i], &(vars->scene.objects));
		else if (file_content[i][0] == 't' && file_content[i][1] == 'r')
			error += parse_triangle(file_content[i], &(vars->scene.objects));
		if (error)
			return (-1);
		i++;
	}
	return (0);
}
