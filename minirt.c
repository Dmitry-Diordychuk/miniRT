/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 21:31:30 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**	trace_ray function
**	if find ray go trought object than we get it's color.
**	if we find two object in one spote we get color of neares.
*/

int		keys_handler(int keycode, t_vars *vars)
{
	static int	camera_number;

	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	if (keycode == 123)
	{
		camera_number--;
		render(vars->screen, &vars->data, vars->scene, camera_number);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	}
	if (keycode == 124)
	{
		camera_number++;
		render(vars->screen, &vars->data, vars->scene, camera_number);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	}
	return (0);
}

int		check_file_name(char *name)
{
	while (ft_strcmp(name, ".rt") != 0 && *name != '\0')
		name++;
	if (*name == '\0')
		return (0);
	return (1);
}

void	init_vars(t_vars *vars)
{
	vars->scene.cameras_counter = 0;
	vars->scene.cameras = NULL;
	vars->scene.lights = NULL;
	vars->scene.objects = NULL;
}

int		main(int argc, char **argv)
{
	t_vars	vars;
	char	**file_content;

	if ((argc < 2 || argc > 3) && !check_file_name(argv[1]))
		return (-1);
	if (!(file_content = get_file_content(argv[1])))
		return (-1);
	init_vars(&vars);
	if (parse_file(file_content, &vars))
		return (-1);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.screen.w, vars.screen.h, "MLX!");
	vars.data.img = mlx_new_image(vars.mlx, vars.screen.w, vars.screen.h);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel,
						&vars.data.line_length, &vars.data.endian);
	if (render(vars.screen, &vars.data, vars.scene, 0) < 0)
		return (-1);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	mlx_hook(vars.win, 2, 1L << 0, keys_handler, &vars);
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		save_image(vars, argv);
	else
		mlx_loop(vars.mlx);
	free_file_content(file_content);
	return (0);
}
