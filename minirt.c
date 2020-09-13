/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/13 03:31:44 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**	trace_ray function
**	if find ray go trought object than we get it's color.
**	if we find two object in one spote we get color of neares.
*/

int	trace_ray(t_scene scene)//t_ray3d r, t_list *objects, t_light_environment env, t_list *lights)
{
	t_object	obj;
	t_object	nearest_obj;
	double		nearest_root;
	t_list		*objects;

	objects = scene.objects;
	nearest_root = -1;
	while (objects != NULL)
	{
		obj = *(t_object*)(objects->content);
		if (apply_intersect(scene.camera.ray, obj, &nearest_root, &nearest_obj) < 0)
			return (-2);
		objects = objects->next;
	}
	if (nearest_root != -1)
	{
		return (color3d_to_trgb(calculate_reflection(scene, nearest_root, nearest_obj)));
	}
	return (-1);
}

int	render_return(int ret, t_list *objects)
{
	ft_lstclear(&objects, delete_object);
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
	// Камера вниз не показывает
	//scene = init_scene(init_objects(), init_lights(), scene.cameras);
	//scene.camera = *(t_camera)scene.cameras;
	scene.camera = *(t_camera*)ft_lstget(scene.cameras, abs(camera_number % scene.cameras_counter)); // 4 заменить на кол-во камер
	point.y = canvas.top_border + 1;
	while (--point.y > canvas.bottom_border)
	{
		point.x = canvas.left_border - 1;
		while (++point.x < canvas.right_border)
		{
			draw_background(img, point, screen, canvas);
			scene.camera.ray.direction = normalize(apply_matrix(scene.camera.rotation_matrix, canvas_to_viewport(point, canvas, scene.camera.viewport)));
			if ((color = trace_ray(scene)) >= 0)
			{
				draw_pixel(img, canvas_to_screen(point, screen), color);
			}
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

t_screen	parse_resolution(char *str)
{
	t_screen	screen;

	str++;
	while (*str == ' ')
		str++;
	screen.width = ft_atoi(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	screen.height = ft_atoi(str);
	return (screen);
}

double	ft_atof(char *str)
{
	int		n;
	double	d;
	int		len;
	int		i;

	d = 0;
	n = ft_atoi(str);
	if ((str = ft_strchr(str, '.')) != NULL)
	{
		str++;
		len = 0;
		while (str[len] != ' ' && str[len] != '\0')
			len++;
		d = ft_atoi(str);
	}
	i = 0;
	while (i < len)
	{
		d = d / 10;
		i++;
	}
	return ((double)n + d);
}

t_color3d	parse_color(char *str)
{
	t_color3d	color;

	color.x = ft_atoi(str);
	str = ft_strchr(str, ',');
	str++;
	color.y = ft_atoi(str);
	str = ft_strchr(str, ',');
	str++;
	color.z = ft_atoi(str);
	return (color);
}

t_light_environment	parse_ambient(char *str)
{
	t_light_environment	amb;

	str++;
	while (*str == ' ')
		str++;
	amb.brightness = ft_atof(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	amb.color = parse_color(str);
	return (amb);
}

t_vector3d	parse_vector(char *str)
{
	t_vector3d	vector;

	vector.x = atof(str);
	str = ft_strchr(str, ',');
	str++;
	vector.y = atof(str);
	str = ft_strchr(str, ',');
	str++;
	vector.z = atof(str);
	return (vector);
}

int	parse_camera(char *str, t_list **cameras)
{
	t_camera camera;
	t_camera *new;

	str++;
	while (*str == ' ')
		str++;
	camera.ray.origin = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	camera.direction = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	camera.fov = ft_atoi(str);
	if (!(new = create_camera(camera.ray.origin, camera.direction, camera.fov)))
		return (-1);
	if (*cameras == NULL)
		*cameras = ft_lstnew((void*)new);                                                   ///malloc
	else
		ft_lstadd_back(cameras, ft_lstnew((void*)new));
	return (0);
}

int	parse_light(char *str, t_list **lights)
{
	t_light_point	light;
	t_light_point	*new;

	str++;
	while (*str == ' ')
		str++;
	light.position = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	light.brightness = ft_atof(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	light.color = parse_color(str);
	if (!(new = create_light_point(light.position, light.brightness, light.color)))
		return (-1);
	if (*lights == NULL)
		*lights = ft_lstnew((void*)new);
	else
		ft_lstadd_back(lights, ft_lstnew((void*)new));
	return (0);
}

int	parse_sphere(char *str, t_list **objects)
{
	t_sphere	sphere;
	t_object	*obj;
	void		*new_sp;
	t_color3d	color;

	str += 2;
	while (*str == ' ')
		str++;
	sphere.position = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	sphere.radius = ft_atof(str) / 2;
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	color = parse_color(str);
	if (!(new_sp = create_sphere(sphere.position, sphere.radius)))
		return (-1);
	if (!(obj = create_object("Sphere", new_sp, color)))
		return (-1);
	if (*objects == NULL)
		*objects = ft_lstnew((void*)obj);
	else
		ft_lstadd_back(objects, ft_lstnew((void*)obj));
	return (0);
}

int	parse_plane(char *str, t_list **objects)
{
	t_plane		plane;
	t_object	*obj;
	void		*new_pl;
	t_color3d	color;

	str += 2;
	while (*str == ' ')
		str++;
	plane.q = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	plane.normal = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	color = parse_color(str);
	if (!(new_pl = create_plane(plane.q, plane.normal)))
		return (-1);
	if (!(obj = create_object("Plane", new_pl, color)))
		return (-1);
	if (*objects == NULL)
		*objects = ft_lstnew((void*)obj);
	else
		ft_lstadd_back(objects, ft_lstnew((void*)obj));
	return (0);
}

int	parse_square(char *str, t_list **objects)
{
	t_square	square;
	t_object	*obj;
	void		*new_sq;
	t_color3d	color;

	str += 2;
	while (*str == ' ')
		str++;
	square.center = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	square.normal = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	square.side = ft_atof(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	color = parse_color(str);
	if (!(new_sq = create_square(square.center, square.normal, square.side)))
		return (-1);
	if (!(obj = create_object("Square", new_sq, color)))
		return (-1);
	if (*objects == NULL)
		*objects = ft_lstnew((void*)obj);
	else
		ft_lstadd_back(objects, ft_lstnew((void*)obj));
	return (0);
}

int	parse_cylinder(char *str, t_list **objects)
{
	t_cylinder	cylinder;
	t_object	*obj;
	void		*new_cy;
	t_color3d	color;

	str += 2;
	while (*str == ' ')
		str++;
	cylinder.position = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	cylinder.center_line = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	cylinder.diameter = ft_atof(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	cylinder.height = ft_atof(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	color = parse_color(str);
	if (!(new_cy = create_cylinder(cylinder.position, cylinder.center_line, cylinder.diameter, cylinder.height)))
		return (-1);
	if (!(obj = create_object("Cylinder", new_cy, color)))
		return (-1);
	if (*objects == NULL)
		*objects = ft_lstnew((void*)obj);
	else
		ft_lstadd_back(objects, ft_lstnew((void*)obj));
	return (0);
}

int	parse_triangle(char *str, t_list **objects)
{
	t_triangle	triangle;
	t_object	*obj;
	void		*new_tr;
	t_color3d	color;

	str += 2;
	while (*str == ' ')
		str++;
	triangle.v1 = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	triangle.v2 = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	triangle.v3 = parse_vector(str);
	str = ft_strchr(str, ' ');
	while (*str == ' ')
		str++;
	color = parse_color(str);
	if (!(new_tr = create_triangle(triangle.v1, triangle.v2, triangle.v3)))
		return (-1);
	if (!(obj = create_object("Triangle", new_tr, color)))
		return (-1);
	if (*objects == NULL)
		*objects = ft_lstnew((void*)obj);
	else
		ft_lstadd_back(objects, ft_lstnew((void*)obj));
	return (0);
}

int	parse_file(char **file_content, t_vars *vars)
{
	int i;

	i = 0;
	while (file_content[i] != NULL)
	{
		if (file_content[i][0] == 'R')
			vars->screen = parse_resolution(file_content[i]);
		if (file_content[i][0] == 'A')
			vars->scene.environment_light = parse_ambient(file_content[i]);
		if (file_content[i][0] == 'c' && file_content[i][1] == ' ')
		{
			parse_camera(file_content[i], &(vars->scene.cameras));
			vars->scene.cameras_counter++;
		}
		if (file_content[i][0] == 'l')
			parse_light(file_content[i], &(vars->scene.lights));
		if (file_content[i][0] == 's' && file_content[i][1] == 'p')
			parse_sphere(file_content[i], &(vars->scene.objects));
		if (file_content[i][0] == 'p' && file_content[i][1] == 'l')
			parse_plane(file_content[i], &(vars->scene.objects));
		if (file_content[i][0] == 's' && file_content[i][1] == 'q')
			parse_square(file_content[i], &(vars->scene.objects));
		if (file_content[i][0] == 'c' && file_content[i][1] == 'y')
			parse_cylinder(file_content[i], &(vars->scene.objects));
		if (file_content[i][0] == 't' && file_content[i][1] == 'r')
			parse_triangle(file_content[i], &(vars->scene.objects));
		i++;
	}
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
	parse_file(file_content, &vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.screen.width, vars.screen.height, "MLX!");
	vars.data.img = mlx_new_image(vars.mlx, vars.screen.width, vars.screen.height);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel,
						&vars.data.line_length, &vars.data.endian);
	if (render(vars.screen, &vars.data, vars.scene, 0) < 0)
		return (-1);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, keys_handler, &vars);
	mlx_loop(vars.mlx);
	free_file_content(file_content);
	return (0);
}

