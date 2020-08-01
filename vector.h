/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:34:01 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/01 15:42:29 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vector3d{
	double	x;
	double	y;
	double	z;
}		t_vector3d;

typedef	t_vector3d t_point3d;
typedef t_vector3d t_color3d;

t_vector3d	sum_vec(t_vector3d a, t_vector3d b);
t_vector3d	minus_vec(t_vector3d a, t_vector3d b);
double		dot_vec(t_vector3d a, t_vector3d b);
t_vector3d	cross_vec(t_vector3d a, t_vector3d b);
t_vector3d	mul_vec_scalar(t_vector3d a, double n);
t_vector3d	div_vec_scalar(t_vector3d a, double n);
double		module_vec(t_vector3d a);

#endif
