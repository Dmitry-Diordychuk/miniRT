/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 03:31:51 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/04 23:00:34 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

/*
**	This function transform canvas point coordinates to viewport coordinates
*/

t_point3d	canvas_to_viewport(t_point2d canvas_point, t_canvas canvas,
							t_viewport viewport)
{
	return ((t_point3d){
			.x = canvas_point.x * (viewport.width / canvas.width) *
									canvas.width / canvas.height,
			.y = canvas_point.y * (viewport.height / canvas.height),
			.z = viewport.focal_length
		});
}

t_matrix4d	generate_rotation_matrix(t_camera camera)
{
	t_matrix4d			m;
	const t_vector3d	prev_direction = (t_vector3d){0,0,1};
	const t_vector3d	up = (t_vector3d){0,1,0};


	m = get_i_mat4d();
//	m = translate(m, (t_vector3d){-camera.ray.origin.x, -camera.ray.origin.y, -camera.ray.origin.z});

	t_vector3d	z = normalize(camera.direction);
	t_vector3d	x = normalize(cross_vec(up, z));
	t_vector3d	y = normalize(cross_vec(z, x));

	m.m00 = x.x;
	m.m01 = y.x;
	m.m02 = z.x;
	m.m10 = x.y;
	m.m11 = y.y;
	m.m12 = z.y;
	m.m20 = x.z;
	m.m21 = y.z;
	m.m22 = z.z;
	m.m30 = -dot_vec(x, camera.ray.origin);
	m.m31 = -dot_vec(y, camera.ray.origin);
	m.m32 = -dot_vec(z, camera.ray.origin);

//	m = translate(m, (t_vector3d){camera.ray.origin.x, camera.ray.origin.y, camera.ray.origin.z});
//	m = rotate_local(
//						m,
//						acos(dot_vec(prev_direction, camera.direction)),
//						unit_vec(cross_vec(prev_direction, camera.direction)),
//						camera.ray.origin
//					);
	return (m);
}

t_camera	*create_camera(t_point3d position, t_viewport viewport, t_vector3d direction, double fov)
{
	t_camera	*camera;

	if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
		return (NULL);
	camera->ray.origin = position;
	camera->viewport = viewport;
	camera->direction = direction;
	camera->rotation_matrix = generate_rotation_matrix(*camera);
	camera->fov = fov;
	return (camera);
}
