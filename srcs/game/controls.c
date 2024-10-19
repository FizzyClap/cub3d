#include "../../includes/cub3D.h"

int	keycode(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	if (keycode == W)
	{
		game->player.y -= 10;
	}
	if (keycode == A)
	{

		game->player.x -= 10;
	}
	if (keycode == S)
	{

		game->player.y += 10;
	}
	if (keycode == D)
	{

		game->player.x += 10;
	}
	return (SUCCESS);
}
