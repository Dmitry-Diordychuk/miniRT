/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 02:50:11 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/12 22:01:36 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_scene	init_scene(t_list *objects, t_list *lights, t_list *cameras)
{
	t_scene	scene;

	scene.objects = objects;
	scene.lights = lights;
	scene.camera = *(t_camera*)(cameras->content);
	return (scene);
}
