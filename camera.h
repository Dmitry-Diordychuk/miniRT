/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 03:30:35 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/11 20:27:19 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <stdlib.h>
# include <libft.h>
# include "point.h"
# include "screen_and_canvas.h"
# include "ray.h"
# include "matrix.h"
# include "transformation.h"

typedef struct		s_viewport
{
	const double	focal_length;
	const double	height;
	const double	width;
}			t_viewport;

typedef	struct		s_camera
{
	t_ray3d		ray;
	t_viewport	viewport;
	t_vector3d	direction;
	t_matrix4d	rotation_matrix;
	double		fov;
}			t_camera;

t_point3d	canvas_to_viewport(t_point2d canvas_point, t_canvas canvas, t_viewport viewport);
t_matrix4d	generate_rotation_matrix(t_camera camera);
t_camera	*create_camera(t_point3d position, t_viewport viewport, t_vector3d direction, double fov);
t_list		*init_cameras();

#endif

