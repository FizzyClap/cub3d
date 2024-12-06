/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:08:01 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:16:28 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	enemy_collision(t_game *game, double x, double y)
{
	if (game->map->lines[(int)y]->content[(int)x] == 'A')
		return (SUCCESS);
	return (FAILURE);
}

void	floor_and_ceiling(t_game *game)
{
	if (game->texture->f_textured)
		floor_raycast(game);
	else
		draw_floor(game, game->floor.a);
	if (game->texture->c_textured)
		ceil_raycast(game);
	else
		draw_ceiling(game, game->ceiling.a);
}
