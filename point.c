/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:03:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/30 15:09:15 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_point4d	p3_to_p4(t_point3d p3)
{
	t_point4d	p4;

	p4.x = p3.x;
	p4.y = p3.y;
	p4.z = p3.z;
	p4.w = 1;
	return (p4);
}

t_point3d	p4_to_p3(t_point4d p4)
{
	t_point3d p3;

	p3.x = p4.x;
	p3.y = p4.y;
	p3.z = p4.z;
	return (p3);
}
