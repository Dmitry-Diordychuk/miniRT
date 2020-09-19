/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:06:03 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/19 22:48:07 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

/*
**	apply intersect function choosen for certain primitive.
*/

int	apply_intersect(t_ray3d r, t_object obj, double *near_t, t_object *near_obj)
{
	double	t;

	t = obj.intersect_function(r, &(obj.container));
	if (*near_t == -1 && t >= 0)
	{
		if (near_obj != NULL)
			*near_obj = obj;
		*near_t = t;
	}
	if (*near_t > t && t >= 0)
	{
		if (near_obj != NULL)
			*near_obj = obj;
		*near_t = t;
	}
	return (0);
}
