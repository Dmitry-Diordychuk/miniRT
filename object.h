/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:34:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/05 03:05:04 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "libft.h"
# include "ray.h"
# include "math.h"
# include "sphere.h"

typedef struct		s_object {
	char		*name;
	void		*obj;
	double		*(*intersect)(t_ray3d ray, void* object);
	t_color3d	color;
}			t_object;

t_object	create_object(const char *name, void *obj, t_color3d color);


#endif
