/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:09:10 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 15:10:07 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# include "minirt.h"

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_data		data;
	t_screen	screen;
	t_scene		scene;
}				t_vars;

#endif
