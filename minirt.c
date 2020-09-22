/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/22 19:28:53 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		keys_handler(int keycode, t_vars *vars)
{
	static int	camera_number;

	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_image(vars->mlx, vars->data.img);
		exit_handler(0, *vars);
	}
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

void	init_vars(t_vars *vars)
{
	vars->scene.cameras_counter = 0;
	vars->scene.cameras = NULL;
	vars->scene.lights = NULL;
	vars->scene.objects = NULL;
	vars->screen.w = 800;
	vars->screen.h = 600;
	vars->scene.camera.direction = (t_vector3d){0, 0, 1};
	vars->scene.camera.fov = 75;
	vars->scene.camera.ray.origin = (t_point3d){0, 0, 0};
	vars->scene.camera.viewport = (t_viewport){1 / (2 * tan((75 / 2) *
														(M_PI / 180))), 1, 1};
	vars->scene.camera.rotation_matrix =
								generate_rotation_matrix(vars->scene.camera);
}

void	mlx_setup(t_vars *vars)
{
	(*vars).win =
		mlx_new_window((*vars).mlx, (*vars).screen.w, (*vars).screen.h, "MLX!");
	mlx_put_image_to_window((*vars).mlx, (*vars).win, (*vars).data.img, 0, 0);
	mlx_hook((*vars).win, 2, 1L << 0, keys_handler, vars);
	mlx_hook((*vars).win, 17, 1L << 17, push_cross_button, vars);
	mlx_loop((*vars).mlx);
}

void	screen_setup(t_vars *vars)
{
	t_screen	screensize;

	mlx_get_screen_size((*vars).mlx, &screensize.w, &screensize.h);
	(*vars).screen.w =
			(*vars).screen.w > screensize.w ? screensize.w : (*vars).screen.w;
	(*vars).screen.h =
			(*vars).screen.h > screensize.h ? screensize.h : (*vars).screen.h;
}

int		main(int argc, char **argv)
{
	t_vars		vars;

	if ((argc < 2 || argc > 3))
		return (show_error(-1, "Error\nToo many arguments!\n"));
	if (!check_file_name(argv[1]))
		return (show_error(-1, "Error\nWrong file format!\n"));
	if (!(vars.file_content = get_file_content(argv[1])))
		return (show_error(-1, "Error\nCan't get file content!\n"));
	init_vars(&vars);
	if (parse_file(&vars))
		return (exit_handler(-1, vars));
	vars.mlx = mlx_init();
	screen_setup(&vars);
	vars.data.img = mlx_new_image(vars.mlx, vars.screen.w, vars.screen.h);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel,
						&vars.data.line_length, &vars.data.endian);
	render(vars.screen, &vars.data, vars.scene, 0);
	if (argc != 3)
		mlx_setup(&vars);
	else if (!ft_strcmp(argv[2], "--save") && save_image(vars, argv))
		return (exit_handler(-3, vars));
	return (exit_handler(0, vars));
}
