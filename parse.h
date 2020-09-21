/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:41:57 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 17:03:22 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minirt.h"

int	parse_resolution(char *str, t_screen *screen);
int	parse_color(char *str, t_color3d *color);
int	parse_ambient(char *str, t_light_environment *amb);
int	parse_vector(char **str, t_vector3d *vector);
int	parse_file(t_vars *vars);

int	skip_spaces(char **str);
int	skip_count_digit(char **str);
int	parse(char *line, t_vars **vars);

int	parse_sphere(char *str, t_list **objects);
int	parse_plane(char *str, t_list **objects);
int	parse_square(char *str, t_list **objects);
int	parse_cylinder(char *str, t_list **objects);
int	parse_triangle(char *str, t_list **objects);

int	parse_camera(char *str, t_list **cameras);
int	parse_light(char *str, t_list **lights);

#endif
