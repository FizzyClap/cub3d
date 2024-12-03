#include "../includes/cub3D_bonus.h"

static void		cam_z(t_game *game, int y);

void	mouse_move(t_game *game)
{
	int	x;
	int	y;

	x = 960;
	y = 540;
	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	if (x < 960)
		left_cam(game);
	if (x > 960)
		right_cam(game);
	if (y != 540)
		cam_z(game, y);
	mlx_mouse_move(game->mlx, game->win, 960, 540);
	game->player.plane_x = -0.66 * sin(game->player.angle);
	game->player.plane_y = 0.66 * cos(game->player.angle);
	game->player.d_x = cos(game->player.angle);
	game->player.d_y = sin(game->player.angle);
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

void	left_cam(t_game *game)
{
	double	oldDirX;
	double oldPlaneX;

	oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(-game->player.rotSpeed) \
	- game->player.dirY * sin(-game->player.rotSpeed);
	game->player.dirY = oldDirX * sin(-game->player.rotSpeed) \
	+ game->player.dirY * cos(-game->player.rotSpeed);
	oldPlaneX = game->player.planeX;
	game->player.planeX = game->player.planeX * cos(-game->player.rotSpeed) \
	- game->player.planeY * sin(-game->player.rotSpeed);
	game->player.planeY = oldPlaneX * sin(-game->player.rotSpeed) \
	+ game->player.planeY * cos(-game->player.rotSpeed);
}

void	right_cam(t_game *game)
{
	double	oldDirX;
	double oldPlaneX;

	oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(game->player.rotSpeed) \
	- game->player.dirY * sin(game->player.rotSpeed);
	game->player.dirY = oldDirX * sin(game->player.rotSpeed) \
	+ game->player.dirY * cos(game->player.rotSpeed);
	oldPlaneX = game->player.planeX;
	game->player.planeX = game->player.planeX * cos(game->player.rotSpeed) \
	- game->player.planeY * sin(game->player.rotSpeed);
	game->player.planeY = oldPlaneX * sin(game->player.rotSpeed) \
	+ game->player.planeY * cos(game->player.rotSpeed);
}

