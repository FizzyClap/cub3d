#include "../includes/cub3D_bonus.h"

int	enemy_collision(t_game *game, double x, double y)
{
	if (game->map->lines[(int)y]->content[(int)x] == 'A')
		return (SUCCESS);
	return (FAILURE);
}
