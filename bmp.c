/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:07:20 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/22 20:49:26 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

void	init_img(char **bmp, t_vars *vars, int header_size)
{
	int		i;
	int		x;
	int		y;
	char	*dst;

	i = header_size;
	y = vars->screen.h - 1;
	while (y > 0)
	{
		x = 0;
		while (x < vars->screen.w)
		{
			dst = vars->data.addr + (y * vars->data.line_length + x *
											(vars->data.bits_per_pixel / 8));
			*(*bmp + i) = *(dst);
			*(*bmp + i + 1) = *(dst + 1);
			*(*bmp + i + 2) = *(dst + 2);
			x++;
			i = i + 3;
		}
		y--;
	}
}

char	*init_bmp(t_vars vars)
{
	const int	header_size = 54;
	int			img_size;
	char		*bmp;

	img_size = vars.screen.w * vars.screen.h * 3 + vars.screen.h * 2;
	if (!(bmp = (char*)ft_calloc(header_size + img_size, sizeof(char))))
		return (NULL);
	*(unsigned short*)bmp = *(unsigned int*)(unsigned long)"BM";
	*(unsigned int*)(bmp + 2) = img_size + header_size;
	*(unsigned short*)(bmp + 6) = 0u;
	*(unsigned short*)(bmp + 8) = 0u;
	*(unsigned int*)(bmp + 10) = header_size;
	*(unsigned int*)(bmp + 14) = 40;
	*(unsigned int*)(bmp + 18) = vars.screen.w;
	*(unsigned int*)(bmp + 22) = vars.screen.h;
	*(unsigned short*)(bmp + 26) = 1;
	*(unsigned short*)(bmp + 28) = 24;
	*(unsigned int*)(bmp + 30) = 0;
	*(unsigned int*)(bmp + 34) = img_size;
	*(unsigned int*)(bmp + 38) = 2835;
	*(unsigned int*)(bmp + 42) = 2835;
	*(unsigned int*)(bmp + 46) = 0;
	*(unsigned int*)(bmp + 50) = 0;
	init_img(&bmp, &vars, header_size);
	return (bmp);
}

int		return_handler(int ret, char *bmp)
{
	if (bmp != NULL)
		free(bmp);
	return (ret);
}

int		save_image(t_vars vars, char **argv)
{
	int		fd;
	char	*filename;
	int		i;
	char	*bmp;

	bmp = NULL;
	if (!(filename = (char*)malloc(sizeof(char) * (ft_strlen(argv[1]) + 2))))
		return (-1);
	i = -1;
	while (argv[1][++i + 2] != '\0')
		filename[i] = argv[1][i];
	filename[i] = 'b';
	filename[i + 1] = 'm';
	filename[i + 2] = 'p';
	filename[i + 3] = '\0';
	if ((fd = open(filename, O_WRONLY | O_CREAT, S_IREAD | S_IWRITE)) < 0)
		return (return_handler(-1, bmp));
	if (!(bmp = init_bmp(vars)))
		return (return_handler(-1, bmp));
	write(fd, bmp, 54 + vars.screen.h * vars.screen.w * 3 + vars.screen.h * 2);
	free(bmp);
	if (close(fd) < 0)
		return (-1);
	return (0);
}
