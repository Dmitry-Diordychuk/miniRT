/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 03:11:41 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/07 03:42:52 by kdustin          ###   ########.fr       */
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

#endif

