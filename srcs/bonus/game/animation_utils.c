/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:05:37 by roespici          #+#    #+#             */
/*   Updated: 2024/12/21 12:08:03 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

double	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec + time.tv_usec / 1000000.0);
}

void	kill_enemy(t_game *game)
{
	t_coord	pos;
	int		target;

	if (game->player.z > -600 && game->player.z < 220)
		target = game->target;
	else
	{
		(void)pos;
		target = -1;
	}
	if (target != -1)
	{
		pos.y = (int)game->enemy[target].y;
		pos.x = (int)game->enemy[target].x;
		Mix_PlayChannel(-1, game->music->hit, 0);
		game->enemy[target].is_animating = true;
		game->enemy[target].start_animation = get_current_time();
	}
}

void	destroy_enemy(t_game *game, int target, t_coord pos)
{
	int	i;

	i = -1;
	while (++i < game->enemy_frames)
	{
		if (game->enemy[target].texture[i].img)
			mlx_destroy_image(game->mlx, game->enemy[target].texture[i].img);
		game->enemy[target].texture[i].img = NULL;
		game->enemy[target].x = -1;
		game->enemy[target].y = -1;
	}
	game->map->lines[pos.y]->content[pos.x] = '0';
}
