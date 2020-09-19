/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:34:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/19 22:39:37 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "libft/libft.h"
# include "ray.h"
# include "math.h"
# include "sphere.h"
# include "plane.h"
# include "square.h"
# include "triangle.h"
# include "cylinder.h"
# include "color.h"
# include "light.h"

typedef struct		s_object {
	char		type[20];
	void		*container;
	double		(*intersect_function)(t_ray3d ray, void **object);
	t_color3d	color;
}			t_object;

void			delete_content(const char *type, void *content);
void			*create_object(const char *type, void *obj, t_color3d color);
void			delete_object(void *object);
t_list			*init_objects();


#endif

