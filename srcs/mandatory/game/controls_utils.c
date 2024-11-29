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
		game->player.d_x = cos(game->player.angle) * 5;
		game->player.d_y = sin(game->player.angle) * 5;
	}
	else
	{
		game->player.x += game->player.d_x * speed;
		game->player.y += game->player.d_y * speed;
	}
}
