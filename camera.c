/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 03:31:51 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 01:42:35 by kdustin          ###   ########.fr       */
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

void		init_lookat_matrix(t_matrix4d *m, t_vector3d forward,
								t_vector3d right, t_vector3d up)
{
	m->m00 = right.x;
	m->m10 = right.y;
	m->m20 = right.z;
	m->m01 = up.x;
	m->m11 = up.y;
	m->m21 = up.z;
	m->m02 = forward.x;
	m->m12 = forward.y;
	m->m22 = forward.z;
}

t_matrix4d	generate_rotation_matrix(t_camera camera)
{
	t_matrix4d			m;
	const t_vector3d	forw = camera.direction;
	const t_vector3d	right = normalize(cross_v((t_vector3d){0, 1, 0}, forw));
	const t_vector3d	up = normalize(cross_v(forw, right));

	m = get_i_mat4d();
	m.m11 = 0;
	m.m22 = 0;
	if (forw.x == 0 && forw.y == 1 && forw.z == 0)
	{
		m.m21 = -1;
		m.m12 = 1;
	}
	else if (forw.x == 0 && forw.y == -1 && forw.z == 0)
	{
		m.m21 = -1;
		m.m12 = -1;
	}
	else
		init_lookat_matrix(&m, forw, right, up);
	m.m30 = -camera.ray.origin.x;
	m.m31 = -camera.ray.origin.y;
	m.m32 = -camera.ray.origin.z;
	return (m);
}

void		*create_camera(t_point3d position, t_vector3d direction, double fov)
{
	t_camera	*camera;

	if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
		return (NULL);
	camera->ray.origin = position;
	camera->viewport =
					(t_viewport){1 / (2 * tan((fov / 2) * (M_PI / 180))), 1, 1};
	camera->direction = normalize(direction);
	camera->rotation_matrix = generate_rotation_matrix(*camera);
	camera->fov = fov;
	return ((void*)camera);
}

void		delete_camera(void *obj)
{
	t_camera	*camera;

	camera = (t_camera*)obj;
	free(camera);
}
