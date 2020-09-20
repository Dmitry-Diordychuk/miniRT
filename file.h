/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 02:32:11 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 14:58:03 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "minirt.h"

char	**resize_content(char **file_content, int size);
char	**get_file_content(char *file);
void	free_file_content(char **file_content);

#endif
