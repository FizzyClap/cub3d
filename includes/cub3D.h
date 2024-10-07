/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:37:18 by roespici          #+#    #+#             */
/*   Updated: 2024/10/07 11:58:44 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "structs.h"
# include "../libft/include/libft.h"
# include "../libft/printf/printf.h"
# include "define.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

void	init_map(t_map *map, char *file);
void	init_texture(t_texture *texture);
//PARSING/CHECK_ARG
int		check_arg(int argc, char **argv);
int		open_file(char *file);
//PARSING/CHECK_CHARACTER
int		nb_start_pos(t_map *map, int y, int x);
int		char_is_valid(char c);
//PARSING/CHECK_MAP
int		read_map(t_map *map, int fd);
//PARSING/CHECK_TEXTURE
int		read_textures(t_texture *texture, char *file);
//PARSING/CHECK_WALLS
int		check_walls(t_map *map, int y, int x);
//FREE
void	free_texture(t_texture *texture);
void	free_map(t_map *map);

#endif
