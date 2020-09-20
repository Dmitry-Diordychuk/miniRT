/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:07:27 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 16:36:22 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include "minirt.h"

char	*init_bmp(t_vars vars);
int		save_image(t_vars vars, char **argv);

#endif
