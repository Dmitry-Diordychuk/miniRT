/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 03:11:41 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 18:24:20 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

typedef struct	s_point2d
{
	int			x;
	int			y;
}				t_point2d;

typedef struct	s_point3d
{
	double		x;
	double		y;
	double		z;
}				t_point3d;

typedef struct	s_point4d
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_point4d;

t_point4d		p3_to_p4(t_point3d p3);
t_point3d		p4_to_p3(t_point4d p4);

#endif
