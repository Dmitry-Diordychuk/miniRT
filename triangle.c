/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 20:31:56 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 01:28:12 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"

void	*create_triangle(t_point3d v1, t_point3d v2, t_point3d v3)
{
	const t_vector3d	v12 = sub_v(v1, v2);
	const t_vector3d	v13 = sub_v(v1, v3);
	const t_vector3d	normal = normalize(cross_v(v12, v13));
	t_triangle			*t;

	if (!(t = (t_triangle*)malloc(sizeof(t_triangle))))
		return (NULL);
	t->v1 = v1;
	t->v2 = v2;
	t->v3 = v3;
	t->normal = normal;
	return ((void*)t);
}
