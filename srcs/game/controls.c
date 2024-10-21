#include "../../includes/cub3D.h"

int	keycode(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	if (keycode == W || keycode == UP)
	{
		game->player.y -= 10;
	}
	if (keycode == A || keycode == LEFT)
	{
		game->player.angle -= 5;
		if (game->player.angle < 0)
			game->player.angle += 360;
	}
	if (keycode == S || keycode == DOWN)
	{
		game->player.y += 10;
	}
	if (keycode == D || keycode == RIGHT)
	{
		game->player.angle += 5;
		if (game->player.angle >= 360)
			game->player.angle -= 360;
	}
	printf("player angle = %f\n", game->player.angle);
	return (SUCCESS);
}
