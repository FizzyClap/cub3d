/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:08:05 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:08:06 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	check_collision(t_game *game, double x, double y);

void	move_up(t_game *game)
{
	double	x;
	double	y;

	x = game->player.pos_x + game->player.dir_x * \
		(game->player.move_speed / game->player.move_div);
	y = game->player. pos_y + game->player.dir_y * \
		(game->player.move_speed / game->player.move_div);
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	if (enemy_collision(game, x, y))
		game_over(game);
}

void	move_down(t_game *game)
{
	double	x;
	double	y;

	x = game->player.pos_x - game->player.dir_x * \
		((game->player.move_speed * 0.5) / game->player.move_div);
	y = game->player.pos_y - game->player.dir_y * \
		((game->player.move_speed * 0.5) / game->player.move_div);
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	if (enemy_collision(game, x, y))
		game_over(game);
}

void	move_left(t_game *game)
{
	double	x;
	double	y;

	x = game->player.pos_x + game->player.dir_y * \
		((game->player.move_speed * 0.5));
	y = game->player.pos_y - game->player.dir_x * \
		((game->player.move_speed * 0.5));
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	if (enemy_collision(game, x, y))
		game_over(game);
}

void	move_right(t_game *game)
{
	double	x;
	double	y;

	x = game->player.pos_x - game->player.dir_y * \
		((game->player.move_speed * 0.5));
	y = game->player.pos_y + game->player.dir_x * \
		((game->player.move_speed * 0.5));
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	if (enemy_collision(game, x, y))
		game_over(game);
}

static void	check_collision(t_game *game, double x, double y)
{
	int	py;
	int	px;

	py = (int)(game->player.pos_y);
	px = (int)(game->player.pos_x);
	if (x > game->player.pos_x && \
	game->map->lines[py]->content[(int)(x + RADIUS)] != '1' && \
	(game->map->lines[py]->content[(int)(x + RADIUS)] != 'D' || \
	is_door_open(game, (int)(x + RADIUS), py)))
		game->player.pos_x = x;
	else if (x < game->player.pos_x && \
	game->map->lines[py]->content[(int)(x - RADIUS)] != '1' && \
	(game->map->lines[py]->content[(int)(x - RADIUS)] != 'D' || \
	is_door_open(game, (int)(x - RADIUS), py)))
		game->player.pos_x = x;
	if (y > game->player.pos_y && \
	game->map->lines[(int)(y + RADIUS)]->content[px] != '1' && \
	(game->map->lines[(int)(y + RADIUS)]->content[px] != 'D' || \
	is_door_open(game, px, (int)(y + RADIUS))))
		game->player.pos_y = y;
	else if (y < game->player.pos_y && \
	game->map->lines[(int)(y - RADIUS)]->content[px] != '1' && \
	(game->map->lines[(int)(y - RADIUS)]->content[px] != 'D' || \
	is_door_open(game, px, (int)(y - RADIUS))))
		game->player.pos_y = y;
}
