#include "../../includes/cub3D.h"

static int	try_move_left(t_game *game);
static int	try_move_right(t_game *game);

void	check_move(t_game *game)
{
	int	left;
	int	right;

	left = try_move_left(game);
	right = try_move_right(game);
	if (left < right)
	{
		game->player.angle -= (double)(left * 0.1);
		correct_angle(game);
		refresh_position(game, DELTA, 0);
		refresh_position(game, MOVE, game->player.speed);
		game->player.angle += (double)(left * 0.1);
		correct_angle(game);
		refresh_position(game, DELTA, 0);
	}
	else
	{
		game->player.angle += (double)(right * 0.1);
		correct_angle(game);
		refresh_position(game, DELTA, 0);
		refresh_position(game, MOVE, game->player.speed);
		game->player.angle -= (double)(right * 0.1);
		correct_angle(game);
		refresh_position(game, DELTA, 0);
	}
}

void	correct_angle(t_game *game)
{
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
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

static int	try_move_left(t_game *game)
{
	double	tmp;
	int		i;
	int		x;
	int		y;

	if (game->player.speed > 0.002)
		game->player.speed -= 0.0005;
	tmp = game->player.angle;
	i = 0;
	x = (game->player.x + game->player.d_x * (game->player.speed));
	y = (game->player.y + game->player.d_y * (game->player.speed));
	while (check_backroom(game, x, y) == FAILURE)
	{
		game->player.angle -= 0.1;
		i++;
		correct_angle(game);
		refresh_position(game, DELTA, 0);
		x = (game->player.x + game->player.d_x * (game->player.speed));
		y = (game->player.y + game->player.d_y * (game->player.speed));
	}
	game->player.angle = tmp;
	refresh_position(game, DELTA, 0);
	return (i);
}

static int	try_move_right(t_game *game)
{
	double	tmp;
	int		i;
	int		x;
	int		y;

	if (game->player.speed > 0.002)
		game->player.speed -= 0.0005;
	tmp = game->player.angle;
	i = 0;
	x = (game->player.x + game->player.d_x * (game->player.speed));
	y = (game->player.y + game->player.d_y * (game->player.speed));
	while (check_backroom(game, x, y) == FAILURE)
	{
		game->player.angle += 0.1;
		i++;
		correct_angle(game);
		refresh_position(game, DELTA, 0);
		x = (game->player.x + game->player.d_x * (game->player.speed));
		y = (game->player.y + game->player.d_y * (game->player.speed));
	}
	game->player.angle = tmp;
	refresh_position(game, DELTA, 0);
	return (i);
}
