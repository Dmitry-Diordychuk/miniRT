/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:44:09 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 23:21:02 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include "color.h"
# include "vector.h"
# include "ray.h"
# include "sphere.h"
# include "object.h"
# include "camera.h"
# include "screen_and_canvas.h"
# include "scene.h"
# include "draw.h"
# include "render.h"
# include "light.h"
# include "reflection.h"
# include "camera.h"
# include "transformation.h"
# include "file.h"
# include "validate.h"
# include "vars.h"
# include "parse.h"
# include "bmp.h"

int	show_error(int ret, char *str);

#endif
