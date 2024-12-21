/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:18:49 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:18:50 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

//UTILS
# define FAILURE 0
# define SUCCESS 1
//180 / PI
# define CENT_PI 57.2957795131
# define PI 3.14159265358
//PI * 2
# define DD_PI 6.28318530718
//PI / 2
# define D_PI 1.57079632679
//PI / 4
# define Q_PI 0.78539816339
# define RADIUS 0.40
# define FOV 60
# define SCREEN_X 1920
# define SCREEN_Y 1080
# define MMW 180
# define MMH 180
# define TILE 20
# define SPEED 0.01
# define MOVE 1
# define DELTA 2
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define MINIMAP_RADIUS 90
# define ERR_ARG "Error: there is 1 argument more than expected\n"
# define ERR_PLAYERS "Error: there is too much start position\n"
# define ERR_EMPTY "Error: line is empty\n"
//KEYCODES
# define ESC 65307
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define A 97
# define W 119
# define D 100
# define S 115
# define SPACE 32
# define SHIFT 65505
# define O 111
# define R 114
//COLORS
# define BLUE 0x000000FF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
//MOVEMENTS
# define MOVEUP 0
# define MOVEBACK 1
# define MOVELEFT 2
# define MOVERIGHT 3

#endif
