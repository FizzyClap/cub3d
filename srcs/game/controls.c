#include "../../includes/cub3D.h"

int	keycode(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	if (keycode == W || keycode == UP)
	{
		if (game->map->lines[(int)game->player.y + (int)game->player.d_y]->content[(int)game->player.x + (int)game->player.x] == '1')
			return (SUCCESS);
		game->player.x += game->player.d_x * game->player.speed;
		game->player.y += game->player.d_y * game->player.speed;
	}
	if (keycode == A || keycode == LEFT)
	{
		game->player.angle -= 0.05;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		game->player.d_x = cos(game->player.angle) * 5;
		game->player.d_y = sin(game->player.angle) * 5;
	}
	if (keycode == S || keycode == DOWN)
	{
		if (game->map->lines[(int)game->player.y + (int)game->player.y]->content[(int)game->player.x + (int)game->player.x] == '1')
			return (SUCCESS);
		game->player.x -= game->player.d_x * game->player.speed;
		game->player.y -= game->player.d_y * game->player.speed;
	}
	if (keycode == D || keycode == RIGHT)
	{
		game->player.angle += 0.05;
		if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
		game->player.d_x = cos(game->player.angle) * 5;
		game->player.d_y = sin(game->player.angle) * 5;
	}
	printf("player angle = %f\n", game->player.angle);
	return (SUCCESS);
}

static void	move_up(t_game *game)
{
	
}
