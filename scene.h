/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 02:46:06 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/07 03:43:52 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "camera.h"
# include "libft.h"

typedef struct		s_scene
{
	t_camera	camera;
	t_list		*objects;
}			t_scene;

t_scene			init_scene(t_list *objects, t_viewport viewport,
							t_point3d origin);

#endif

