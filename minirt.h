/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:44:09 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/05 13:45:49 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <math.h>
# include "mlx.h"
# include "color.h"
# include "vector.h"
# include "ray.h"
# include "sphere.h"
# include "object.h"
# include "camera.h"
# include "screen_and_canvas.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_data;

#endif
