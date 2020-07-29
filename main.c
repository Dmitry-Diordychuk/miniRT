/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 21:46:40 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/29 23:23:54 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_data;

typedef struct	s_point {
	int	x;
	int	y;
}		t_point;

void	draw_pixel(t_data *data, t_point p, int color)
{
	char *dst;

	dst = data->addr +
		(p.y * data->line_length + p.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line_brute(t_data *data, t_point p1, t_point p2, int color)
{
	float k;
	float b;

	if (abs(p2.x - p1.x) >= abs(p2.y - p1.y))
	{
		k = (float)(p2.y - p1.y) / (float)(p2.x - p1.x);
		b = (float)(p1.y * p2.x - p2.y * p1.x) / (float)(p2.x - p1.x);
		if (p1.x > p2.x)
			ft_intswap(&p1.x, &p2.x);
		while (p1.x <= p2.x)
			draw_pixel(data, (t_point){p1.x++, k * p1.x + b},
									color);
	}
	else
	{
		k = (float)(p2.x - p1.x) / (float)(p2.y - p1.y);
		b = (float)(p1.x * p2.y - p2.x * p1.y) / (float)(p2.y - p1.y);
		if (p1.y > p2.y)
			ft_intswap(&p1.y, &p2.y);
		while (p1.y <= p2.y)
			draw_pixel(data, (t_point){k * p1.y + b, p1.y++},
									color);
	}
}

int	main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "MLX!");
	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_line_brute(&img, (t_point){310, 200}, (t_point){300, 300}, 0xff0000);
	draw_line_brute(&img, (t_point){410, 200}, (t_point){300, 300}, 0x00ff00);
	draw_line_brute(&img, (t_point){410, 300}, (t_point){300, 300}, 0x0000ff);
	draw_line_brute(&img, (t_point){410, 400}, (t_point){300, 300}, 0xff0000);
	draw_line_brute(&img, (t_point){310, 400}, (t_point){300, 300}, 0x00ff00);
	draw_line_brute(&img, (t_point){210, 400}, (t_point){300, 300}, 0x0000ff);
	draw_line_brute(&img, (t_point){210, 300}, (t_point){300, 300}, 0xff0000);
	draw_line_brute(&img, (t_point){210, 200}, (t_point){300, 300}, 0x00ff00);
	draw_pixel(&img, (t_point){300, 300}, 0xc46f1a);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

