#include "../includes/cub3D.h"

static double	try_move_left(t_game *game);
static double	try_move_right(t_game *game);

void	check_move(t_game *game)
{
	double	left;
	double	right;

	left = try_move_left(game);
	right = try_move_right(game);
	if (left < right && left > 0.25)
	{
		game->player.angle -= (PI / 6);
		correct_angle(game);
		refresh_position(game, DELTA, 0);
		refresh_position(game, MOVE, game->player.speed);
		game->player.angle += (PI / 6);
	}
	else if (right > 0.25 && right != 145000)
	{
		game->player.angle += (PI / 6);
		correct_angle(game);
		refresh_position(game, DELTA, 0);
		refresh_position(game, MOVE, game->player.speed);
		game->player.angle -= (PI / 6);
	}
	correct_angle(game);
	refresh_position(game, DELTA, 0);
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

static double	try_move_left(t_game *game)
{
	double	result;
	double	x;
	double	y;

	if (game->player.speed > 0.002)
		game->player.speed -= 0.0005;
	game->player.angle -= PI / 6;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = (game->player.x + game->player.d_x * (game->player.speed));
	y = (game->player.y + game->player.d_y * (game->player.speed));
	result = check_backroom(game, x, y);
	game->player.angle += PI / 6;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	if (result > 0.25)
		return (result);
	else
		return (0);
}

static double	try_move_right(t_game *game)
{
	double	result;
	double	x;
	double	y;

	if (game->player.speed > 0.002)
		game->player.speed -= 0.0005;
	game->player.angle += PI / 6;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = (game->player.x + game->player.d_x * (game->player.speed));
	y = (game->player.y + game->player.d_y * (game->player.speed));
	result = check_backroom(game, x, y);
	game->player.angle -= PI / 6;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	if (result > 0.25)
		return (result);
	else
		return (145000);
}
