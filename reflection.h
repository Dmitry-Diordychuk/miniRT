/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 01:04:56 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/22 20:37:25 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFLECTION_H
# define REFLECTION_H

# include "scene.h"
# include "intersection.h"

typedef	struct			s_reflection_data
{
	t_point3d			point;
	t_vector3d			normal;
	t_light_directional	light;
	double				specular;
	t_color3d			obj_color;
	t_color3d			light_color;
}						t_reflection_data;

t_color3d				calculate_reflection(t_scene scene, double nearest_root,
												t_object nearest_obj);

#endif
