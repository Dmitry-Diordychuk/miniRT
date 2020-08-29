/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 13:53:48 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/29 18:19:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

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
}				t_matrix4d;


t_matrix3d	init_mat(t_matrix3d m);
t_matrix3d	mul_mat_scalar(double a, t_matrix3d);

#endif
