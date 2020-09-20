/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:31:01 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 02:32:06 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

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
