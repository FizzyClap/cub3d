#include "../includes/cub3D.h"

static double	cam_sensibility(int x);

void	mouse_move(t_game *game)
{
	int			x;
	int			y;

	x = 960;
	y = 540;
	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	if (x < 960)
		left_cam(game, x);
	if (x > 960)
		right_cam(game, x);
	mlx_mouse_move(game->mlx, game->win, 960, 540);
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

int	check_backroom(t_game *game, int x, int y)
{
	if (game->map->lines[y]->content[x] == '1')
		return (FAILURE);
	if (y > game->player.y && game->map->lines[y - 1] && \
	game->map->lines[y - 1]->content[x] == '1')
		return (FAILURE);
	if (x > game->player.x && game->map->lines[y]->content[x - 1] && \
	game->map->lines[y]->content[x - 1] == '1')
		return (FAILURE);
	return (SUCCESS);
}
