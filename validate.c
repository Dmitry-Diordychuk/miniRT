/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:39:38 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 02:42:15 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validate.h"

int	validate_int(char *str)
{
	int counter;

	counter = 0;
	while (ft_isdigit(*str))
	{
		str++;
		counter++;
	}
	if (ft_isspace(*str) || *str == '\0')
		return (0);
	return (-1);
}

int	validate_double(char *str)
{
	int counter;

	counter = 0;
	while (ft_isdigit(*str))
	{
		str++;
		counter++;
	}
	if (*str == '.')
	{
		counter++;
		str++;
		while (ft_isdigit(*str))
		{
			str++;
			counter++;
		}
	}
	if (ft_isspace(*str) || *str == '\0')
		return (0);
	return (-1);
}
