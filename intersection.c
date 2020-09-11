/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:06:03 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/11 15:27:40 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

/*
**	apply intersect function choosen for certain primitive.
*/

int	apply_intersect(t_ray3d r, t_object obj, double *nearest_root,
							t_object *nearest_obj)
{
	double	root;

	root = obj.intersect_function(r, obj.container);
	if (*nearest_root == -1 && root >= 0)
	{
		if (nearest_obj != NULL)
			*nearest_obj = obj;
		*nearest_root = root;
	}
	if (*nearest_root > root && root >= 0)
	{
		if (nearest_obj != NULL)
			*nearest_obj = obj;
		*nearest_root = root;
	}
	return (0);
}
