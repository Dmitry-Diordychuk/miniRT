/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 19:21:43 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 02:05:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_H
# define TRANSFORMATION_H

# include <math.h>
# include "matrix.h"

t_matrix4d	translate(t_matrix4d m, t_vector3d v);
t_matrix4d	rotate(t_matrix4d m, double a, t_vector3d v);
t_matrix4d	rotate_local(t_matrix4d m, double a, t_vector3d v, t_vector3d obj);
t_vector3d	apply_matrix(t_matrix4d m, t_vector3d target);

#endif
