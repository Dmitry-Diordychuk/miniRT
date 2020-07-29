/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 21:46:40 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/29 17:37:54 by kdustin          ###   ########.fr       */
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

void	draw_pixel(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	float y;
	float k;
	float b;
	float a;

	b = (y2 - y1);
	a = (x2 - x1);
	if (fabs(a) >= fabs(b) && a != 0)
	{
		k = b / a;
		b = (y1 * x2 - y2 * x1) / a;
		if (x1 > x2)
			ft_intswap(&x1, &x2);
		while (x1 <= x2)
		{
			y = k * x1 + b; 
			draw_pixel(data, x1, y, color); 
 			x1++;
		}
	}
	else if (fabs(a) < fabs(b) && b != 0)
	{
		k = a / b;
		b = (x1 * y2 - x2 * y1) / b;
		if (y1 > y2)
			ft_intswap(&y1, &y2);
		while (y1 <= y2)
		{
			y = y1 * k + b;
			draw_pixel(data, y, y1, color);
			y1++;
		}
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
	draw_line(&img, 300, 200, 300, 300, 0xff0000);
	draw_line(&img, 400, 200, 300, 300, 0x00ff00);
	draw_line(&img, 400, 300, 300, 300, 0x0000ff);
	draw_line(&img, 400, 400, 300, 300, 0xff0000);
	draw_line(&img, 300, 400, 300, 300, 0x00ff00);
	draw_line(&img, 200, 400, 300, 300, 0x0000ff);
	draw_line(&img, 200, 300, 300, 300, 0xff0000);
	draw_line(&img, 200, 200, 300, 300, 0x00ff00);
	draw_pixel(&img, 300, 300, 0xc46f1a);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

