/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 03:31:51 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/19 22:00:58 by kdustin          ###   ########.fr       */
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
	t_matrix4d			orientation;
	t_matrix4d			translation;
	orientation = get_i_mat4d();
	translation = get_i_mat4d();
	t_vector3d	forward = camera.direction;
	t_vector3d	right = normalize(cross_v((t_vector3d){0, 1, 0}, forward));
	t_vector3d	up = normalize(cross_v(forward, right));

	if (camera.direction.x == 0 && camera.direction.y == 1 && camera.direction.z == 0)
	{
		orientation.m11 = 0;
		orientation.m21 = -1;
		orientation.m12 = 1;
		orientation.m22 = 0;
	}
	else if (camera.direction.x == 0 && camera.direction.y == -1 && camera.direction.z == 0)
	{
		orientation.m11 = 0;
		orientation.m21 = -1;
		orientation.m12 = -1;
		orientation.m22 = 0;
	}
	else
	{
		orientation.m00 = right.x;
		orientation.m10 = right.y;
		orientation.m20 = right.z;
		orientation.m01 = up.x;
		orientation.m11 = up.y;
		orientation.m21 = up.z;
		orientation.m02 = forward.x;
		orientation.m12 = forward.y;
		orientation.m22 = forward.z;
	}
	translation.m30 = -camera.ray.origin.x;
	translation.m31 = -camera.ray.origin.y;
	translation.m32 = -camera.ray.origin.z;
	return (mul_mat4d(orientation, translation));
}

void	*create_camera(t_point3d position, t_vector3d direction, double fov)
{
	t_camera	*camera;

	if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
		return (NULL);
	camera->ray.origin = position;
	camera->viewport = (t_viewport){1 / (2 * tan((fov / 2) * (M_PI / 180))), 1, 1};
	camera->direction = normalize(direction);
	camera->rotation_matrix = generate_rotation_matrix(*camera);
	camera->fov = fov;
	return ((void*)camera);
}

void	delete_camera(void *obj)
{
	t_camera	*camera;

	camera = (t_camera*)obj;
	free(camera);
}
