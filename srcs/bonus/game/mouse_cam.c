#include "../includes/cub3D_bonus.h"

static void		cam_z(t_game *game, int y);
static double	cam_sensibility(int x);

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
	double	oldDirX;
	double oldPlaneX;

	oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(-(cam_sensibility(x))) \
	- game->player.dirY * sin(-(cam_sensibility(x)));
	game->player.dirY = oldDirX * sin(-(cam_sensibility(x))) \
	+ game->player.dirY * cos(-(cam_sensibility(x)));
	oldPlaneX = game->player.planeX;
	game->player.planeX = game->player.planeX * cos(-(cam_sensibility(x))) \
	- game->player.planeY * sin(-(cam_sensibility(x)));
	game->player.planeY = oldPlaneX * sin(-(cam_sensibility(x))) \
	+ game->player.planeY * cos(-(cam_sensibility(x)));
}

void	right_cam(t_game *game, int x)
{
	double	oldDirX;
	double oldPlaneX;

	oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(cam_sensibility(x)) \
	- game->player.dirY * sin(cam_sensibility(x));
	game->player.dirY = oldDirX * sin(cam_sensibility(x)) \
	+ game->player.dirY * cos(cam_sensibility(x));
	oldPlaneX = game->player.planeX;
	game->player.planeX = game->player.planeX * cos(cam_sensibility(x)) \
	- game->player.planeY * sin(cam_sensibility(x));
	game->player.planeY = oldPlaneX * sin(cam_sensibility(x)) \
	+ game->player.planeY * cos(cam_sensibility(x));
}

static double	cam_sensibility(int x)
{
	x -= 960;
	if (x < 0)
		x *= -1;
	return ((double)(x * 0.0005));
}

