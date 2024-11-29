#include "../includes/cub3D_bonus.h"

// static double	try_move_left(t_game *game, int move);
// static double	try_move_right(t_game *game, int move);

// void	check_move(t_game *game, int move)
// {
// 	double	left;
// 	double	right;

// 	left = try_move_left(game, move);
// 	right = try_move_right(game, move);
// 	if (left < right && left >= 0.2)
// 	{
// 		game->player.angle -= (0.5);
// 		correct_angle(game);
// 		refresh_position(game, DELTA, 0);
// 		refresh_position(game, MOVE, game->player.speed);
// 		game->player.angle += (0.5);
// 	}
// 	else if (right > 0.25 && right < INT_MAX)
// 	{
// 		game->player.angle += (0.5);
// 		correct_angle(game);
// 		refresh_position(game, DELTA, 0);
// 		refresh_position(game, MOVE, game->player.speed);
// 		game->player.angle -= (0.5);
// 	}
// 	correct_angle(game);
// 	refresh_position(game, DELTA, 0);
// }

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
		game->player.d_x = cos(game->player.angle);
		game->player.d_y = sin(game->player.angle);
	}
	else
	{
		game->player.x += game->player.d_x * speed / game->player.move_div;
		game->player.y += game->player.d_y * speed / game->player.move_div;
	}
}

// static double	try_move_left(t_game *game, int move)
// {
// 	double	result;

// 	game->player.angle -= 0.8;
// 	correct_angle(game);
// 	refresh_position(game, DELTA, 0);
// 	result = check_backroom(game, move);
// 	game->player.angle += 0.8;
// 	correct_angle(game);
// 	refresh_position(game, DELTA, 0);
// 	if (result > 0.2)
// 		return (result);
// 	else
// 		return (0);
// }

// static double	try_move_right(t_game *game, int move)
// {
// 	double	result;

// 	game->player.angle += 0.8;
// 	correct_angle(game);
// 	refresh_position(game, DELTA, 0);
// 	result = check_backroom(game, move);
// 	game->player.angle -= 0.8;
// 	correct_angle(game);
// 	refresh_position(game, DELTA, 0);
// 	if (result > 0.2)
// 		return (result);
// 	else
// 		return (INT_MAX);
// }
