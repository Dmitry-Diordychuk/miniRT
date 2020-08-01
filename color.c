/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 17:10:22 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/01 20:42:56 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(unsigned int trgb)
{
	return (((0xff << 24) & trgb) >> 24);
}

int	get_r(unsigned int trgb)
{
	return (((0xff << 16) & trgb) >> 16);
}

int	get_g(unsigned int trgb)
{
	return (((0xff << 8) & trgb) >> 8);
}

int	get_b(unsigned int trgb)
{
	return (0xff & trgb);
}
