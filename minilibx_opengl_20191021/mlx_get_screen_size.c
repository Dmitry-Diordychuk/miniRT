/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_screen_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 19:23:38 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 20:27:36 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <CoreGraphics/CGDisplayConfiguration.h>

int		mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	int mainDisplayId = CGMainDisplayID();
	*sizex = CGDisplayPixelsWide(mainDisplayId);
	*sizey = CGDisplayPixelsHigh(mainDisplayId);
	return (0);
}
