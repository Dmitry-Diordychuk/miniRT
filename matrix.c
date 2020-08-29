/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 13:53:52 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/29 18:18:37 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix3d	init_mat(t_matrix3d m)
{
	m.m00 = 0;
	m.m01 = 0;
	m.m02 = 0;
	m.m10 = 0;
	m.m11 = 0;
	m.m12 = 0;
	m.m20 = 0;
	m.m21 = 0;
	m.m22 = 0;

	return (m);
}

t_matrix3d	mul_mat_scalar(double a, t_matrix3d m)
{
	m.m00 = m.m00 * a;
	m.m01 = m.m01 * a;
	m.m02 = m.m02 * a;
	m.m10 = m.m10 * a;
	m.m11 = m.m11 * a;
	m.m12 = m.m12 * a;
	m.m20 = m.m20 * a;
	m.m21 = m.m21 * a;
	m.m22 = m.m22 * a;

	return (m);
}
