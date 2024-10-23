#include "../../includes/cub3D.h"

void	mouse_move(t_game *game)
{
	int			x;
	int			y;

	x = 960;
	y = 540;
	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	if (x < 950)
		left_cam(game, x);
	if (x > 970)
		right_cam(game, x);
	mlx_mouse_move(game->mlx, game->win, 960, 540);
}

static double	cam_sensibility(int x)
{
	x -= 960;
	if (x < 0)
		x *= -1;
	return ((double)(x * 0.001));
}

void	left_cam(t_game *game, int x)
{

	game->player.angle -= cam_sensibility(x);
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	game->player.d_x = cos(game->player.angle) * 5;
	game->player.d_y = sin(game->player.angle) * 5;
}

void	right_cam(t_game *game, int x)
{
	game->player.angle += cam_sensibility(x);
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
	game->player.d_x = cos(game->player.angle) * 5;
	game->player.d_y = sin(game->player.angle) * 5;
}
