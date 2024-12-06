/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:12:25 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:12:27 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	correct_angle(t_game *game)
{
	if (game->player.angle < 0)
		game->player.angle += DD_PI;
	if (game->player.angle > DD_PI)
		game->player.angle -= DD_PI;
}

void	refresh_position(t_game *game, int action, double speed)
{
	if (action == DELTA)
	{
		game->player.dir_x = cos(game->player.angle);
		game->player.dir_y = sin(game->player.angle);
	}
	else
	{
		game->player.x += game->player.dir_x * speed / game->player.move_div;
		game->player.y += game->player.dir_y * speed / game->player.move_div;
	}
}
