/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:12:50 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:12:51 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	check_collision(t_game *game, double x, double y);

void	move_up(t_game *game)
{
	double	x;
	double	y;

	x = game->player.x + (game->player.dir_x * \
	(game->player.move_speed / game->player.move_div));
	y = game->player.y + (game->player.dir_y * \
	(game->player.move_speed / game->player.move_div));
	check_collision(game, x, y);
}

void	move_down(t_game *game)
{
	double	x;
	double	y;

	x = game->player.x - (game->player.dir_x * \
	(game->player.move_speed / game->player.move_div));
	y = game->player.y - (game->player.dir_y * \
	(game->player.move_speed / game->player.move_div));
	check_collision(game, x, y);
}

void	move_left(t_game *game)
{
	double	x;
	double	y;

	game->player.angle -= D_PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = game->player.x + (game->player.dir_x * \
	(game->player.move_speed / game->player.move_div));
	y = game->player.y + (game->player.dir_y * \
	(game->player.move_speed / game->player.move_div));
	check_collision(game, x, y);
	game->player.angle += D_PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
}

void	move_right(t_game *game)
{
	double	x;
	double	y;

	game->player.angle += D_PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = game->player.x + (game->player.dir_x * \
	(game->player.move_speed / game->player.move_div));
	y = game->player.y + (game->player.dir_y * \
	(game->player.move_speed / game->player.move_div));
	check_collision(game, x, y);
	game->player.angle -= D_PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
}

static void	check_collision(t_game *game, double x, double y)
{
	int	py;
	int	px;

	py = (int)(game->player.y);
	px = (int)(game->player.x);
	if (x > game->player.x && \
	game->map->lines[py]->content[(int)(x + RADIUS)] != '1')
		game->player.x = x;
	else if (x < game->player.x && \
	game->map->lines[py]->content[(int)(x - RADIUS)] != '1')
		game->player.x = x;
	if (y > game->player.y && \
	game->map->lines[(int)(y + RADIUS)]->content[px] != '1')
		game->player.y = y;
	else if (y < game->player.y && \
	game->map->lines[(int)(y - RADIUS)]->content[px] != '1')
		game->player.y = y;
}
