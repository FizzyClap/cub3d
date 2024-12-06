/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:07:08 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:15:48 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	make_actions(t_game *game)
{
	draw_minimap(game, game->raycast);
	if (game->player.action[MOVEUP] == 1)
		move_up(game);
	if (game->player.action[MOVEBACK] == 1)
		move_down(game);
	if (game->player.action[MOVELEFT] == 1)
		move_left(game);
	if (game->player.action[MOVERIGHT] == 1)
		move_right(game);
}

int	keyrelease(int keycode, t_game *game)
{
	if (keycode == W || keycode == UP)
		game->player.action[MOVEUP] = 0;
	if (keycode == A)
		game->player.action[MOVELEFT] = 0;
	if (keycode == S || keycode == DOWN)
		game->player.action[MOVEBACK] = 0;
	if (keycode == D)
		game->player.action[MOVERIGHT] = 0;
	if (keycode == RIGHT)
		right_cam(game, 970);
	if (keycode == LEFT)
		left_cam(game, 950);
	if (keycode == SHIFT)
	{
		if (game->player.move_speed == 0.05)
			game->player.move_speed = 0.1;
		else if (game->player.move_speed == 0.1)
			game->player.move_speed = 0.05;
	}
	if (keycode == ESC)
		close_game(game);
	return (SUCCESS);
}

int	keycode(int keycode, t_game *game)
{
	if (keycode == O)
		shoot_ray_to_center(game, true);
	if (keycode == R)
	{
		if (game->anim_weapons.is_animating == false)
		{
			game->anim_weapons.is_animating = true;
			game->anim_weapons.start_animation = get_current_time();
			Mix_PlayChannel(-1, game->music->weapon, 0);
		}
	}
	if (keycode == W || keycode == UP)
		game->player.action[MOVEUP] = 1;
	if (keycode == S || keycode == DOWN)
		game->player.action[1] = 1;
	if (keycode == A)
		game->player.action[2] = 1;
	if (keycode == D)
		game->player.action[3] = 1;
	if (keycode == RIGHT)
		right_cam(game, 970);
	if (keycode == LEFT)
		left_cam(game, 950);
	return (SUCCESS);
}

void	move_div(t_game *game)
{
	int	result;

	result = 0;
	if (game->player.action[MOVEUP] == 1)
		result++;
	if (game->player.action[MOVELEFT] == 1)
		result++;
	if (game->player.action[MOVERIGHT] == 1)
		result++;
	if (game->player.action[MOVEBACK] == 1)
		result++;
	game->player.move_div = result;
}

int	mouse_game(int button, int x, int y, t_game *game)
{
	(void)button;
	(void)y;
	(void)x;
	if (game->anim_weapons.is_animating == false)
	{
		game->anim_weapons.is_animating = true;
		game->anim_weapons.start_animation = get_current_time();
		Mix_PlayChannel(-1, game->music->weapon, 0);
	}
	return (SUCCESS);
}
