/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:34:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/05 22:32:20 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "libft.h"
# include "ray.h"
# include "math.h"
# include "sphere.h"
# include "color.h"

typedef struct		s_object {
	char		type[20];
	void		*container;
	double		*(*intersect_function)(t_ray3d ray, void* object);
	t_color3d	color;
}			t_object;

t_object	*create_object(const char *type, void *obj, t_color3d color);

#endif
