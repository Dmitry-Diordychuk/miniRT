/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 17:04:48 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 19:21:18 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "point.h"

typedef t_point3d	t_color3d;

int			to_trgb(t_color3d color);
int			create_trgb(int t, int r, int g, int b);

#endif
