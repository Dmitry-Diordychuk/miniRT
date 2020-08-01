/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 17:04:48 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/01 17:37:52 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

int	create_trgb(int t, int r, int g, int b);
int	get_t(unsigned int trgb);
int	get_r(unsigned int trgb);
int	get_g(unsigned int trgb);
int	get_b(unsigned int trgb);

#endif
