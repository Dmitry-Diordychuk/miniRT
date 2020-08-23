/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:06:51 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/23 17:10:57 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "ray.h"
# include "object.h"

int	apply_intersect(t_ray3d r, t_object obj, double *nearest_root,
														t_object *nearest_obj);

#endif
