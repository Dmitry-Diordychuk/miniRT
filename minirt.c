/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 02:38:25 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**	trace_ray function
**	if find ray go trought object than we get it's color.
**	if we find two object in one spote we get color of neares.
*/

int	keys_handler(int keycode, t_vars *vars)
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

int	check_file_name(char *name)
{
	while (ft_strcmp(name, ".rt") != 0 && *name != '\0')
		name++;
	if (*name == '\0')
		return (0);
	return (1);
}

char	*init_bmp(t_vars vars)
{
	const int header_size = 54;//54;
	const int img_size = vars.screen.width * vars.screen.height * 3 + vars.screen.height * 2;
	char *bmp;

	if (!(bmp = (char*)ft_calloc(header_size + img_size, sizeof(char))))
		return (NULL);
	*(unsigned short*)bmp = *(unsigned int*)(unsigned long)"BM";
	*(unsigned int*)(bmp + 2) = img_size + header_size;
	*(unsigned short*)(bmp + 6) = 0u;
	*(unsigned short*)(bmp + 8) = 0u;
	*(unsigned int*)(bmp + 10) = header_size;
	*(unsigned int*)(bmp + 14) = 40;
	*(unsigned int*)(bmp + 18) = vars.screen.width;
	*(unsigned int*)(bmp + 22) = vars.screen.height;
	*(unsigned short*)(bmp + 26) = 1;
	*(unsigned short*)(bmp + 28) = 24;
	*(unsigned int*)(bmp + 30) = 0;
	*(unsigned int*)(bmp + 34) = img_size;
	*(unsigned int*)(bmp + 38) = 2835;
	*(unsigned int*)(bmp + 42) = 2835;
	*(unsigned int*)(bmp + 46) = 0;
	*(unsigned int*)(bmp + 50) = 0;
	int i;
	int x;
	int y;
	char *dst;

	i = header_size;
	y = vars.screen.height - 1;
	while (y > 0)
	{
		x = 0;
		while (x < vars.screen.width)
		{
			dst = vars.data.addr + (y * vars.data.line_length + x * (vars.data.bits_per_pixel / 8));
			*(bmp + i) = *(dst);
			*(bmp + i + 1) = *(dst + 1);
			*(bmp + i + 2) = *(dst + 2);
			x++;
			i = i + 3;
		}
		y--;
	}
	return (bmp);
}

int	save_image(t_vars vars, char **argv)
{
	int		fd;
	char	*filename;
	int		i;
	char	*bmp;

	if (!(filename = (char*)malloc(sizeof(char) * (ft_strlen(argv[1]) + 2))))
		return (-1);
	i = 0;
	while (argv[1][i + 2] != '\0')
	{
		filename[i] = argv[1][i];
		i++;
	}
	filename[i] = 'b';
	filename[i + 1] = 'm';
	filename[i + 2] = 'p';
	filename[i + 3] = '\0';
	if ((fd = open(filename, O_WRONLY | O_CREAT, S_IREAD | S_IWRITE)) < 0)
		return (-1);
	if (!(bmp = init_bmp(vars)))
		return (-1);
	write(fd, bmp, 54 + vars.screen.height * vars.screen.width * 3 + vars.screen.height * 2);
	//free(bmp);
	if (close(fd) < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	char	**file_content;

	if (argc < 2 || argc > 3)
		return (-1);
	if (!check_file_name(argv[1]))
		return (-1);
	if (!(file_content = get_file_content(argv[1])))
		return (-1);
	vars.scene.cameras_counter = 0;
	vars.scene.cameras = NULL;
	vars.scene.lights = NULL;
	vars.scene.objects = NULL;
	if (parse_file(file_content, &vars))
		return (-1);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.screen.width, vars.screen.height, "MLX!");
	vars.data.img = mlx_new_image(vars.mlx, vars.screen.width, vars.screen.height);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel,
						&vars.data.line_length, &vars.data.endian);
	if (render(vars.screen, &vars.data, vars.scene, 0) < 0)
		return (-1);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, keys_handler, &vars);
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		save_image(vars, argv);
	else
		mlx_loop(vars.mlx);
	free_file_content(file_content);
	return (0);
}

