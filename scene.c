/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 02:50:11 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/07 16:14:40 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_scene	init_scene(t_list *objects, t_list *lights,
	t_light_environment env_light,t_viewport viewport, t_point3d origin )
{
	t_scene	scene;

	scene.objects = objects;
	scene.lights = lights;
	scene.environment_light = env_light;
	scene.camera.viewport = viewport;
	scene.camera.ray.origin = origin;	
	return (scene);
}
