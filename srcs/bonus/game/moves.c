#include "../includes/cub3D.h"

void	move_up(t_game *game)
{
	double	x;
	double	y;

	x = game->player.x + (game->player.d_x * \
	(game->player.speed / game->player.move_div));
	y = game->player.y + (game->player.d_y * \
	(game->player.speed / game->player.move_div));
	if (x > game->player.x && \
	game->map->lines[(int)(game->player.y)]->content[(int)(x + RADIUS)] != '1')
		game->player.x = x;
	else if (x < game->player.x && \
	game->map->lines[(int)(game->player.y)]->content[(int)(x - RADIUS)] != '1')
		game->player.x = x;
	if (y > game->player.y && \
	game->map->lines[(int)(y + RADIUS)]->content[(int)(game->player.x)] != '1')
		game->player.y = y;
	else if (y < game->player.y && \
	game->map->lines[(int)(y - RADIUS)]->content[(int)(game->player.x)] != '1')
		game->player.y = y;
}

void	move_down(t_game *game)
{
	double	x;
	double	y;

	x = game->player.x - (game->player.d_x * \
	(game->player.speed / game->player.move_div));
	y = game->player.y - (game->player.d_y * \
	(game->player.speed / game->player.move_div));
	if (x > game->player.x && \
	game->map->lines[(int)(game->player.y)]->content[(int)(x + RADIUS)] != '1')
		game->player.x = x;
	else if (x < game->player.x && \
	game->map->lines[(int)(game->player.y)]->content[(int)(x - RADIUS)] != '1')
		game->player.x = x;
	if (y > game->player.y && \
	game->map->lines[(int)(y + RADIUS)]->content[(int)(game->player.x)] != '1')
		game->player.y = y;
	else if (y < game->player.y && \
	game->map->lines[(int)(y - RADIUS)]->content[(int)(game->player.x)] != '1')
		game->player.y = y;
}

void	move_left(t_game *game)
{
	double	x;
	double	y;

	game->player.angle -= D_PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = game->player.x + (game->player.d_x * \
	(game->player.speed / game->player.move_div));
	y = game->player.y + (game->player.d_y * \
	(game->player.speed / game->player.move_div));
	if (x > game->player.x && \
	game->map->lines[(int)(game->player.y)]->content[(int)(x + RADIUS)] != '1')
		game->player.x = x;
	else if (x < game->player.x && \
	game->map->lines[(int)(game->player.y)]->content[(int)(x - RADIUS)] != '1')
		game->player.x = x;
	if (y > game->player.y && \
	game->map->lines[(int)(y + RADIUS)]->content[(int)(game->player.x)] != '1')
		game->player.y = y;
	else if (y < game->player.y && \
	game->map->lines[(int)(y - RADIUS)]->content[(int)(game->player.x)] != '1')
		game->player.y = y;
	game->player.angle += D_PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
}

void	move_right(t_game *game)
{
	double	x;
	double	y;

	game->player.angle += D_PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = game->player.x + (game->player.d_x * \
	(game->player.speed / game->player.move_div));
	y = game->player.y + (game->player.d_y * \
	(game->player.speed / game->player.move_div));
	if (x > game->player.x && \
	game->map->lines[(int)(game->player.y)]->content[(int)(x + RADIUS)] != '1')
		game->player.x = x;
	else if (x < game->player.x && \
	game->map->lines[(int)(game->player.y)]->content[(int)(x - RADIUS)] != '1')
		game->player.x = x;
	if (y > game->player.y && \
	game->map->lines[(int)(y + RADIUS)]->content[(int)(game->player.x)] != '1')
		game->player.y = y;
	else if (y < game->player.y && \
	game->map->lines[(int)(y - RADIUS)]->content[(int)(game->player.x)] != '1')
		game->player.y = y;
	game->player.angle -= D_PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
}
