/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 01:04:56 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/11 01:11:37 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFLECTION_H
# define REFLECTION_H

# include "scene.h"

double	calculate_reflection(t_scene scene, double nearest_root,
							t_object nearest_obj);

double			calculate_diffuse_reflection(t_point3d point,
				t_vector3d norm, t_light_environment env,
								t_list *lights);

#endif
