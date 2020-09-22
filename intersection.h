/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:06:51 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/22 19:26:21 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "ray.h"
# include "object.h"

void	apply_intersect(t_ray3d r, t_object obj, double *nearest_root,
														t_object *nearest_obj);

#endif
