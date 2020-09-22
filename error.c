/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:49:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/22 19:29:03 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	show_error(int ret, char *str)
{
	ft_putstr_fd(str, 1);
	return (-1);
}

int	exit_handler(int ret, t_vars vars)
{
	if (ret == -3)
		show_error(ret, "Error\nCan't save image!\n");
	if (vars.scene.objects != NULL)
		ft_lstclear(&vars.scene.objects, delete_object);
	if (vars.scene.cameras != NULL)
		ft_lstclear(&vars.scene.cameras, delete_camera);
	if (vars.scene.lights != NULL)
		ft_lstclear(&vars.scene.lights, delete_light);
	if (vars.file_content != NULL)
		free_file_content(vars.file_content);
	exit(ret);
	return (ret);
}

int	check_file_name(char *name)
{
	while (ft_strcmp(name, ".rt") != 0 && *name != '\0')
		name++;
	if (*name == '\0')
		return (0);
	return (1);
}

int	push_cross_button(t_vars *vars)
{
	exit_handler(0, *vars);
	return (0);
}
