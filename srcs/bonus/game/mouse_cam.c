#include "../includes/cub3D.h"

static double	cam_sensibility(int x);
static void		cam_z(t_game *game, int y);

void	mouse_move(t_game *game)
{
	int	x;
	int	y;

	x = 960;
	y = 540;
	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	if (x < 960)
		left_cam(game, x);
	if (x > 960)
		right_cam(game, x);
	if (y != 540)
		cam_z(game, y);
	mlx_mouse_move(game->mlx, game->win, 960, 540);
}

static void	cam_z(t_game *game, int y)
{
	int	z;

	z = 540 - y;
	game->player.z += z;
	if (game->player.z > 3000)
		game->player.z = 3000;
	if (game->player.z < -3000)
		game->player.z = -3000;
}

void	left_cam(t_game *game, int x)
{
	game->player.angle -= cam_sensibility(x);
	if (game->player.angle < 0)
		game->player.angle += DD_PI;
	refresh_position(game, DELTA, 0);
}

void	right_cam(t_game *game, int x)
{
	game->player.angle += cam_sensibility(x);
	if (game->player.angle > DD_PI)
		game->player.angle -= DD_PI;
	refresh_position(game, DELTA, 0);
}

static double	cam_sensibility(int x)
{
	x -= 960;
	if (x < 0)
		x *= -1;
	return ((double)(x * 0.001));
}
