/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 13:53:48 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 14:58:48 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef	struct	s_matrix4d
{
	double		m00;
	double		m01;
	double		m02;
	double		m03;
	double		m10;
	double		m11;
	double		m12;
	double		m13;
	double		m20;
	double		m21;
	double		m22;
	double		m23;
	double		m30;
	double		m31;
	double		m32;
	double		m33;
}				t_matrix4d;

t_matrix4d		mul_mat4d(t_matrix4d a, t_matrix4d b);
t_matrix4d		get_i_mat4d(void);
t_vector4d		mul_mat4d_vec4d(t_matrix4d m, t_vector4d v);

#endif
