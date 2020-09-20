/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:34:01 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 14:52:59 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "point.h"

typedef	t_point3d	t_vector3d;
typedef t_point4d	t_vector4d;

t_vector3d		sum_v(t_vector3d a, t_vector3d b);
t_vector3d		sub_v(t_vector3d a, t_vector3d b);
double			dot_v(t_vector3d a, t_vector3d b);
t_vector3d		cross_v(t_vector3d a, t_vector3d b);
double			module_v(t_vector3d a);

t_vector3d		normalize(t_vector3d a);
t_vector4d		v3_to_v4(t_vector3d v);
t_vector3d		v4_to_v3(t_vector4d v);
t_vector3d		mul_vs(t_vector3d a, double n);
t_vector3d		div_vs(t_vector3d a, double n);

#endif
