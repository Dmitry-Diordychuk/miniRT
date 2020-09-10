/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:23:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/09 14:06:55 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "libft/libft.h"
# include "vector.h"
# include "object.h"

typedef struct		s_light_point
{
	t_point3d	position;
	double		brightness;
}			t_light_point;

typedef struct		s_light_directional
{
	t_vector3d	direction;
	double		brightness;
}			t_light_directional;

typedef struct		s_light_environment
{
	double		brightness;
	t_color3d	color;
}			t_light_environment;

t_list			*init_lights();
void			*create_light_point(t_point3d position,
							double brightness);
void			*create_light_directional(t_vector3d direction,
							double brightness);

#endif
