/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 02:46:06 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/11 20:35:04 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H


# include "camera.h"
# include "libft/libft.h"
# include "light.h"

typedef struct			s_scene
{
	t_camera			camera;
	t_list				*objects;
	t_list				*lights;
	t_list				*cameras;
	t_light_environment	environment_light;
}						t_scene;

t_scene				init_scene(t_list *objects, t_list *lights, t_list *cameras,
							t_light_environment env_light);

#endif

