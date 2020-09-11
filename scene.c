/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 02:50:11 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/11 20:42:56 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_scene	init_scene(t_list *objects, t_list *lights, t_list *cameras,
	t_light_environment env_light)
{
	t_scene	scene;

	scene.objects = objects;
	scene.lights = lights;
	scene.cameras = cameras;
	scene.environment_light = env_light;
	scene.camera = *(t_camera*)cameras->content;
	return (scene);
}
