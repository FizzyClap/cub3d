#include "../../includes/cub3D.h"

int	keycode(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	return (SUCCESS);
}
