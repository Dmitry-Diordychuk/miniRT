/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:39:12 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 02:48:33 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	skip_spaces(char **str)
{
	int counter;

	counter = 0;
	while (ft_isspace(**str))
	{
		(*str)++;
		counter++;
	}
	if (counter != 0)
		return (0);
	return (-1);
}

int	skip_count_digit(char **str)
{
	int counter;

	counter = 0;
	if (**str == '-')
		(*str)++;
	while (ft_isdigit(**str))
	{
		(*str)++;
		counter++;
	}
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			(*str)++;
			counter++;
		}
	}
	return (counter);
}

void	skip_vector(char **str)
{
	if (**str == '-')
		(*str)++;
	while (ft_isdigit(**str) || **str == '.')
		(*str)++;
	(*str)++;
	if (**str == '-')
		(*str)++;
	while (ft_isdigit(**str) || **str == '.')
		(*str)++;
	(*str)++;
	if (**str == '-')
		(*str)++;
	while (ft_isdigit(**str) || **str == '.')
		(*str)++;
}
