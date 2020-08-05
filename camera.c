/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 03:31:51 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/05 03:44:20 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

/*
**	This function transform canvas point coordinates to viewport coordinates
*/

t_point3d	canvas_to_viewport(t_point2d canvas_point, t_canvas canvas, t_viewport viewport)
{
	return ((t_point3d){
		.x = canvas_point.x * (viewport.width / canvas.width) * 4 / 3,
		.y = canvas_point.y * (viewport.height / canvas.height), 
		.z = viewport.focal_length
		});
}
