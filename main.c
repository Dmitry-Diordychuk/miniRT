/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 21:46:40 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/30 15:47:18 by kdustin          ###   ########.fr       */
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
	float	x;
	float	y;
}		t_point;

void	draw_pixel(t_data *data, t_point p, int color)
{
	char *dst;

	dst = data->addr +
	((int)p.y * data->line_length + (int)p.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
**	This function use math formula y = kx + b. We need to reverse axes when
**	k angle is bigger than 1, because step of y became bigger than step of
**	x.
*/

void	draw_line_brute(t_data *data, t_point p1, t_point p2, int color)
{
	float k;
	float b;

	if (fabs(p2.x - p1.x) >= fabs(p2.y - p1.y))
	{
		k = (p2.y - p1.y) / (p2.x - p1.x);
		b = (p1.y * p2.x - p2.y * p1.x) / (p2.x - p1.x);
		if (p1.x > p2.x)
			ft_floatswap(&p1.x, &p2.x);
		while (p1.x <= p2.x)
			draw_pixel(data, (t_point){p1.x++, k * p1.x + b},
									color);
	}
	else
	{
		k = (p2.x - p1.x) / (p2.y - p1.y);
		b = (p1.x * p2.y - p2.x * p1.y) / (p2.y - p1.y);
		if (p1.y > p2.y)
			ft_floatswap(&p1.y, &p2.y);
		while (p1.y <= p2.y)
			draw_pixel(data, (t_point){k * p1.y + b, p1.y++},
									color);
	}
}

void	point_swap(t_point *p1, t_point *p2)
{
	t_point temp;
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

/*
**	This algoritm use k slope. We choose wich of side of line triangle is
**	bigger and wich is smaller. The bigger side get plus 1 every step. The
**	smaller side get plus k (slope) and it will be incremented at the step
**	when it can be rounded to bigger number.
*/

void	draw_line_dda(t_data *data, t_point p1, t_point p2, int color)
{
	float	dx;	
	float	dy;
	int	i;
	int	steps;

	if (fabs(p2.x - p1.x) >= fabs(p2.y - p1.y))
	{
		steps = fabs(p2.x - p1.x);
		p1.x > p2.x ? point_swap(&p1, &p2) : 0;
	}
	else
	{
		steps = fabs(p2.y - p1.y);
		p1.y > p2.y ? point_swap(&p1, &p2) : 0;	
	}
	dx = (p2.x - p1.x) / steps;
	dy = (p2.y - p1.y) / steps;
	i = 0;
	while (i++ < steps + 1)
	{
		draw_pixel(data, (t_point){round(p1.x), round(p1.y)}, color);
		p1.x = p1.x + dx;
		p1.y = p1.y + dy;
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
	draw_line_dda(&img, (t_point){300, 200}, (t_point){300, 300}, 0xff0000);
	draw_line_dda(&img, (t_point){400, 200}, (t_point){300, 300}, 0x00ff00);
	draw_line_dda(&img, (t_point){400, 300}, (t_point){300, 300}, 0x0000ff);
	draw_line_dda(&img, (t_point){400, 400}, (t_point){300, 300}, 0xff0000);
	draw_line_dda(&img, (t_point){300, 400}, (t_point){300, 300}, 0x00ff00);
	draw_line_dda(&img, (t_point){200, 400}, (t_point){300, 300}, 0x0000ff);
	draw_line_dda(&img, (t_point){200, 300}, (t_point){300, 300}, 0xff0000);
	draw_line_dda(&img, (t_point){200, 200}, (t_point){300, 300}, 0x00ff00);
	draw_pixel(&img, (t_point){300, 300}, 0xc46f1a);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

