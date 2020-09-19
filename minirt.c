/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/19 22:16:38 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**	trace_ray function
**	if find ray go trought object than we get it's color.
**	if we find two object in one spote we get color of neares.
*/

int	trace_ray(t_scene scene)
{
	t_object	obj;
	t_object	near_obj;
	double		near_root;
	t_list		*objects;

	objects = scene.objects;
	near_root = -1;
	while (objects != NULL)
	{
		obj = *(t_object*)(objects->content);
		if (apply_intersect(scene.camera.ray, obj, &near_root, &near_obj) < 0)
			return (-2);
		objects = objects->next;
	}
	if (near_root != -1)
	{
		return (color3d_to_trgb(calculate_reflection(scene, near_root, near_obj)));
	}
	return (-1);
}

int	render_return(int ret, t_list *objects)
{
	//ft_lstclear(&objects, delete_object);                                   //Переделать или другое место
	return (ret);
}

void	*ft_lstget(t_list *list, int number)
{
	int	i;

	i = 0;
	while (i < number && list != NULL)
	{
		list = list->next;
		i++;
	}
	if (list != NULL)
		return (list->content);
	return (NULL);
}
                                                                                //  разобратся с t_data, разобратся с цветами  initobj initlight malloc
int	render(t_screen screen, t_data *img, t_scene scene,int camera_number)
{
	const t_canvas	canvas = create_canvas(screen);
	t_point2d		point;
	int				color;
	t_list			*lights;
	int				test;

	scene.camera = *(t_camera*)ft_lstget(scene.cameras, abs(camera_number % scene.cameras_counter));
	point.y = canvas.top_border + 1;
	while (--point.y > canvas.bottom_border)
	{
		point.x = canvas.left_border - 1;
		while (++point.x < canvas.right_border)
		{
			draw_background(img, point, screen, canvas);
			scene.camera.ray.direction = normalize(apply_matrix(scene.camera.rotation_matrix, canvas_to_viewport(point, canvas, scene.camera.viewport)));
			if ((color = trace_ray(scene)) >= 0)
				draw_pixel(img, canvas_to_screen(point, screen), color);
			else if (color == -2)
				return (render_return(-2, scene.objects));
		}
	}
	return (render_return(0, scene.objects));
}

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_data		data;
	t_screen	screen;
	t_scene		scene;
}				t_vars;

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

char	**resize_content(char **file_content, int size)
{
	char	**new_file_content;
	int		i;

	if (!(new_file_content = (char**)malloc(sizeof(char*) * size)))
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		new_file_content[i] = file_content[i];
		i++;
	}
	free(file_content);
	return (new_file_content);
}

char	**get_file_content(char *file)
{
	int		fd;
	char	**file_content;
	int		i;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	file_content = (char**)malloc(sizeof(char*));
	i = 0;
	while (get_next_line(fd, &file_content[i]))
	{
		i++;
		if (!(file_content = resize_content(file_content, i + 1)))
			return (NULL);
	}
	i++;
	if (!(file_content = resize_content(file_content, i + 1)))
		return (NULL);
	file_content[i] = NULL;
	if (close(fd))
		return (NULL);
	return (file_content);
}

void	free_file_content(char **file_content)
{
	int i;

	i = 0;
	while (file_content[i] != NULL)
	{
		free(file_content[i]);
		i++;
	}
	free(file_content);
}

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

int	parse_resolution(char *str, t_screen *screen)
{
	int			error;

	error = 0;
	str++;
	error += skip_spaces(&str);
	error += validate_int(str);
	screen->width = ft_atoi(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += validate_int(str);
	screen->height = ft_atoi(str);
	return (error);
}

double	ft_atof(char *str)
{
	int		n;
	double	d;
	int		len;
	int		sign;

	sign = 1;
	if (str[0] == '-' && str[1] == '0')
		sign = -1;
	d = 0;
	len = 0;
	n = ft_atoi(str);
	while (ft_isdigit(*str) || *str == '-')
		str++;
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(str[len]))
			len++;
		d = ft_atoi(str);
	}
	while (len-- > 0)
		d = d / 10;
	return (((double)n + d) * sign);
}

int	parse_color(char *str, t_color3d *color)
{
	int	counter;

	color->x = ft_atoi(str);
	counter = 0;
	counter += skip_count_digit(&str);
	if (*str != ',' || counter > 3 || counter == 0 || color->x > 255 || color->x < 0)
		return (-1);
	str++;
	color->y = ft_atoi(str);
	counter = 0;
	counter += skip_count_digit(&str);
	if (*str != ',' || counter > 3 || counter == 0 || color->y > 255 || color->y < 0)
		return (-1);
	str++;
	color->z = ft_atoi(str);
	counter = 0;
	counter += skip_count_digit(&str);
	if ((!ft_isspace(*str) && *str != '\0') || counter > 3 || counter == 0 || color->z > 255 || color->z < 0)
		return (-1);
	return (0);
}

int	parse_ambient(char *str, t_light_environment *amb)
{
	int	error;

	error = 0;
	str++;
	error += skip_spaces(&str);
	error += validate_double(str);
	amb->brightness = ft_atof(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &(amb->color));
	return (error);
}

int	parse_vector(char *str, t_vector3d *vector)
{
	vector->x = ft_atof(str);
	skip_count_digit(&str);
	if (*str == '.' && str++)
		skip_count_digit(&str);
	if (*str != ',')
		return (-1);
	str++;
	vector->y = ft_atof(str);
	skip_count_digit(&str);
	if (*str == '.' && str++)
		skip_count_digit(&str);
	if (*str != ',')
		return (-1);
	str++;
	vector->z = ft_atof(str);
	skip_count_digit(&str);
	if (*str == '.' && str++)
		skip_count_digit(&str);
	if (!ft_isspace(*str) && *str != '\0')
		return (-1);
	return (0);
}

void	ft_lstpush(t_list **list, t_list *elem)
{
	if (*list == NULL)
		*list = elem;
	else
		ft_lstadd_back(list, elem);
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

int	parse_camera(char *str, t_list **cameras)
{
	t_camera	c;
	void		*new_camera;
	int			error;
	t_list		*new_elem;

	error = 0;
	str++;
	error += skip_spaces(&str);
	error += parse_vector(str, &(c.ray.origin));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(c.direction));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += validate_double(str);
	c.fov = ft_atoi(str);
	if (!(new_camera = create_camera(c.ray.origin, c.direction, c.fov)))
		return (error - 1);
	if (!(new_elem = ft_lstnew(new_camera)))
	{
		free(new_camera);
		return (error - 1);
	}
	ft_lstpush(cameras, new_elem);
	return (error);
}

int	parse_light(char *str, t_list **lights)
{
	t_light_point	light;
	void			*new_light;
	t_list			*new_elem;
	int				error;

	error = 0;
	str++;
	error += skip_spaces(&str);
	error += parse_vector(str, &(light.position));
	skip_vector(&str);
	error += skip_spaces(&str);
	light.brightness = ft_atof(str);
	error += validate_double(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &(light.color));
	if (!(new_light = create_light_point(light.position, light.brightness, light.color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new_light)))
		return (-1);
	ft_lstpush(lights, new_elem);
	return (error);
}

int	parse_sphere(char *str, t_list **objects)
{
	t_sphere	sphere;
	void		*new;
	t_color3d	color;
	int			error;
	t_list		*new_elem;

	error = 0;
	str += 2;
	error += skip_spaces(&str);
	error += parse_vector(str, &(sphere.position));
	skip_vector(&str);
	error += skip_spaces(&str);
	sphere.radius = ft_atof(str) / 2;
	error += validate_double(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &color);
	if (!(new = create_sphere(sphere.position, sphere.radius)))                  //malloc free
		return (-1);
	if (!(new = create_object("Sphere", new, color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new)))
		return (-1);
	ft_lstpush(objects, new_elem);
	return (error);
}

int	parse_plane(char *str, t_list **objects)
{
	t_plane		plane;
	void		*new;
	t_list		*new_elem;
	t_color3d	color;
	int			error;

	error = 0;
	str += 2;
	error += skip_spaces(&str);
	error += parse_vector(str, &(plane.q));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(plane.normal));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &color);
	if (!(new = create_plane(plane.q, plane.normal)))
		return (-1);
	if (!(new = create_object("Plane", new, color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new)))
		return (-1);
	ft_lstpush(objects, new_elem);
	return (error);
}

int	parse_square(char *str, t_list **objects)
{
	t_square	square;
	void		*new;
	t_list		*new_elem;
	t_color3d	color;
	int			error;

	error = 0;
	str += 2;
	error += skip_spaces(&str);
	error += parse_vector(str, &(square.center));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(square.normal));
	skip_vector(&str);
	error += skip_spaces(&str);
	square.side = ft_atof(str);
	error += validate_double(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &color);
	if (!(new = create_square(square.center, square.normal, square.side)))
		return (-1);
	if (!(new = create_object("Square", new, color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new)))
		return (-1);
	ft_lstpush(objects, new_elem);
	return (error);
}

int	parse_cylinder(char *str, t_list **objects)
{
	t_cylinder	cylinder;
	void		*new;
	t_list		*new_elem;
	t_color3d	color;
	int			error;

	error = 0;
	str += 2;
	error += skip_spaces(&str);
	error += parse_vector(str, &(cylinder.position));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(cylinder.direction));
	skip_vector(&str);
	error += skip_spaces(&str);
	cylinder.d = ft_atof(str);
	error += validate_double(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	cylinder.h = ft_atof(str);
	error += validate_double(str);
	skip_count_digit(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &color);
	if (!(new = create_cylinder(cylinder.position, cylinder.direction, cylinder.d, cylinder.h)))
		return (-1);
	if (!(new = create_object("Cylinder", new, color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new)))
		return (-1);
	ft_lstpush(objects, new_elem);
	return (error);
}

int	parse_triangle(char *str, t_list **objects)
{
	t_triangle	triangle;
	void		*new;
	t_list		*new_elem;
	t_color3d	color;
	int			error;

	error = 0;
	str += 2;
	error += skip_spaces(&str);
	error += parse_vector(str, &(triangle.v1));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(triangle.v2));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_vector(str, &(triangle.v3));
	skip_vector(&str);
	error += skip_spaces(&str);
	error += parse_color(str, &color);
	if (!(new = create_triangle(triangle.v1, triangle.v2, triangle.v3)))
		return (-1);
	if (!(new = create_object("Triangle", new, color)))
		return (-1);
	if (!(new_elem = ft_lstnew(new)))
		return (-1);
	ft_lstpush(objects, new_elem);
	return (error);
}

int	parse_file(char **file_content, t_vars *vars)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (file_content[i] != NULL)
	{
		if (file_content[i][0] == 'R')
			error += parse_resolution(file_content[i], &vars->screen);
		else if (file_content[i][0] == 'A')
			error += parse_ambient(file_content[i], &(vars->scene.environment_light));
		else if (file_content[i][0] == 'c' && ft_isspace(file_content[i][1]))
		{
			error += parse_camera(file_content[i], &(vars->scene.cameras));
			vars->scene.cameras_counter++;
		}
		else if (file_content[i][0] == 'l')
			error += parse_light(file_content[i], &(vars->scene.lights));
		else if (file_content[i][0] == 's' && file_content[i][1] == 'p')
			error += parse_sphere(file_content[i], &(vars->scene.objects));
		else if (file_content[i][0] == 'p' && file_content[i][1] == 'l')
			error += parse_plane(file_content[i], &(vars->scene.objects));
		else if (file_content[i][0] == 's' && file_content[i][1] == 'q')
			error += parse_square(file_content[i], &(vars->scene.objects));
		else if (file_content[i][0] == 'c' && file_content[i][1] == 'y')
			error += parse_cylinder(file_content[i], &(vars->scene.objects));
		else if (file_content[i][0] == 't' && file_content[i][1] == 'r')
			error += parse_triangle(file_content[i], &(vars->scene.objects));
		if (error)
			return (-1);
		i++;
	}
	return (0);
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

