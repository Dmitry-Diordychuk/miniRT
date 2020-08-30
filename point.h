/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 03:11:41 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/30 03:59:36 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

typedef struct	s_point2d
{
	int	x;
	int	y;
}		t_point2d;

typedef struct	s_point3d
{
	double	x;
	double	y;
	double	z;
}		t_point3d;

typedef struct	s_point4d
{
	double x;
	double y;
	double z;
	double w;
}				t_point4d;


#endif

