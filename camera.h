/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 03:30:35 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/07 03:45:06 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "screen_and_canvas.h"
# include "ray.h"

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
}			t_camera;

t_point3d		canvas_to_viewport(t_point2d canvas_point,
					t_canvas canvas, t_viewport viewport);

#endif

