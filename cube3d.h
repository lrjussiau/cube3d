/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:17:04 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/20 11:24:26 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include "libft/libft.h"

typedef struct s_map
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_color;
	char	*cell_color;
	int		*player_pos;
	char	player_orientation;
	char	**map;
	char	**file;
}		t_map;

//utils
void	ft_print_map(char **tab);
void	error(char *str);
void	*safe_malloc(unsigned int bytes);

//map_parsing
void	parsing_map(char *path, t_map *map);

//map_parsing_utils
char	*str_append(const char *str1, const char *str2);
char	*clear_path(char *str);
char	*clear_color(char *str);

#endif