/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 13:53:48 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/30 04:31:40 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

#include "vector.h"

typedef	struct	s_matrix3d
{
	double	m00;
	double	m01;
	double	m02;
	double	m10;
	double	m11;
	double	m12;
	double	m20;
	double	m21;
	double	m22;
}				t_matrix3d;

typedef	struct	s_matrix4d
{
	double	m00;
	double	m01;
	double	m02;
	double	m03;
	double	m10;
	double	m11;
	double	m12;
	double	m13;
	double	m20;
	double	m21;
	double	m22;
	double	m23;
	double	m30;
	double	m31;
	double	m32;
	double	m33;
}				t_matrix4d;


t_matrix3d	init_mat3d(t_matrix3d m);
t_matrix3d	mul_mat3d_scalar(double a, t_matrix3d);
t_matrix3d	sum_mat3d(t_matrix3d a, t_matrix3d b);
t_matrix3d	mul_mat3d(t_matrix3d a, t_matrix3d b);
t_matrix3d	get_i_mat3d();
t_matrix3d	mul_mat3d_vec(t_matrix3d m, t_vector3d v);
t_matrix3d	trans_mat3d(t_matrix3d m);
double		det_mat(t_matrix3d m);
t_matrix3d	invert_mat3d(t_matrix3d m);

t_matrix4d	init_mat4d(t_matrix4d m);
t_matrix4d	mul_mat4d_scalar(double a, t_matrix4d);
t_matrix4d	sum_mat4d(t_matrix4d a, t_matrix4d b);
t_matrix4d	mul_mat4d(t_matrix4d a, t_matrix4d b);
t_matrix4d	get_i_mat4d();
t_matrix4d	trans_mat4d(t_matrix4d m);
t_vector4d	mul_mat4d_vec4d(t_matrix4d m, t_vector4d v);
#endif
