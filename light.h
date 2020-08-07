/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:23:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/07 14:25:01 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h"

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
}			t_light_environment;

#endif
