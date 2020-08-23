/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:06:03 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/23 17:06:07 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

/*
**	apply intersect function choosen for certain primitive.
*/

int	apply_intersect(t_ray3d r, t_object obj, double *nearest_root,
							t_object *nearest_obj)
{
	double	*roots;

	if (!(roots = obj.intersect_function(r, obj.container)))
		return (-1);
	if ((roots[0] > 0 || roots[1] > 0) &&
	(*nearest_root == -1 || *nearest_root == 0 || roots[0] < *nearest_root || roots[1] < *nearest_root))
	{
		if (nearest_obj != NULL)
			*nearest_obj = obj;
		if (roots[0] < 0)
			*nearest_root = roots[1];
		else if (roots[1] < 0)
			*nearest_root = roots[0];
		else if (roots[0] < roots[1])
			*nearest_root = roots[0];
		else
			*nearest_root = roots[1];;
	}
	free(roots);
	return (0);
}
