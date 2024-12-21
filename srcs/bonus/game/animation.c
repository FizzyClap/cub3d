/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:05:44 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:05:45 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

t_image	*doors_animation(t_game *game, int idx, int start)
{
	int		current_frame;
	double	elapsed_time;

	elapsed_time = game->time - game->doors[idx].start_animation;
	if (elapsed_time < 0)
		elapsed_time = 0;
	if (game->doors[idx].is_animating == false)
	{
		if (game->doors[idx].is_open == true)
			return (&game->door[game->doors_frames - 1]);
		else
			return (&game->door[0]);
	}
	current_frame = (int)(elapsed_time / 0.1);
	if (current_frame >= game->doors_frames)
	{
		current_frame = game->doors_frames - 1;
		game->doors[idx].is_animating = false;
	}
	if (start == 0)
		current_frame = game->doors_frames - 1 - current_frame;
	return (&game->door[current_frame]);
}

t_image	*weapon_animation(t_game *game)
{
	int		current_frame;
	double	elapsed_time;

	elapsed_time = game->time - game->anim_weapons.start_animation;
	if (elapsed_time < 0)
		elapsed_time = 0;
	if (game->anim_weapons.is_animating == false)
		return (&game->weapon[0]);
	current_frame = (int)(elapsed_time / 0.1);
	if (current_frame >= game->weapons_frames)
	{
		current_frame = game->weapons_frames - 1;
		game->anim_weapons.is_animating = false;
	}
	if (current_frame == game->weapons_frames - 1)
	{
		shoot_ray_to_center(game, false);
		kill_enemy(game);
	}
	return (&game->weapon[current_frame]);
}

t_image	*enemy_animation(t_game *game, int target, t_coord pos)
{
	int		current_frame;
	double	elapsed_time;

	elapsed_time = game->time - game->enemy[target].start_animation;
	if (elapsed_time < 0)
		elapsed_time = 0;
	if (game->enemy[target].is_animating == false)
		return (&game->enemy[target].texture[0]);
	current_frame = (int)(elapsed_time / 0.1);
	if (current_frame >= game->enemy_frames)
	{
		current_frame = game->enemy_frames - 1;
		game->enemy[target].is_animating = false;
	}
	if (current_frame == game->enemy_frames - 1)
		destroy_enemy(game, target, pos);
	return (&game->enemy[target].texture[current_frame]);
}

void	*gollum(t_game *game)
{
	int		current_frame;
	double	elapsed_time;
	double	adjusted_time;

	elapsed_time = game->time - game->launcher_start_animation;
	if (elapsed_time < 0)
		elapsed_time = 0;
	if (elapsed_time >= 4 * 0.1 && elapsed_time < (4 * 0.1 + 3.5))
		adjusted_time = 4 * 0.1;
	else if (elapsed_time >= (4 * 0.1 + 3.5))
		adjusted_time = elapsed_time - 3.5;
	else
		adjusted_time = elapsed_time;
	if (game->launcher_animation == false)
		return (game->launcher[0].img);
	current_frame = (int)(adjusted_time / 0.1);
	if (current_frame >= game->launcher_frames)
	{
		current_frame = game->launcher_frames - 1;
		game->launcher_animation = false;
	}
	return (game->launcher[current_frame].img);
}
