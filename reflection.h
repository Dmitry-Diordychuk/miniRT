/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 01:04:56 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/12 13:35:55 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFLECTION_H
# define REFLECTION_H

# include "scene.h"

typedef	struct				s_reflection_data
{
		t_point3d		point;
		t_vector3d		normal;
		t_light_directional	light;
		double			specular;
}					t_reflection_data;

double	calculate_reflection(t_scene scene, double nearest_root,
							t_object nearest_obj);

#endif
