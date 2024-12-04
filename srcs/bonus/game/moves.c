#include "../includes/cub3D_bonus.h"

static void	check_collision(t_game *game, double x, double y);

void	move_up(t_game *game)
{
	double	x;
	double	y;

	x = game->player.posX + game->player.dirX * (game->player.moveSpeed / game->player.move_div);
	y = game->player. posY + game->player.dirY * (game->player.moveSpeed / game->player.move_div);
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	//if (enemy_collision(game, x, y))
		//game_over(game);
}

void	move_down(t_game *game)
{
	double	x;
	double	y;

	x = game->player.posX - game->player.dirX * (game->player.moveSpeed / game->player.move_div);
	y = game->player.posY - game->player.dirY * (game->player.moveSpeed / game->player.move_div);
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	//if (enemy_collision(game, x, y))
	//	game_over(game);
}

void	move_left(t_game *game)
{
	double	x;
	double	y;

	x = game->player.posX + game->player.dirY * (game->player.moveSpeed / game->player.move_div);
	y = game->player.posY - game->player.dirX * (game->player.moveSpeed / game->player.move_div);
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	// if (enemy_collision(game, x, y))
	//     game_over(game);
}


void	move_right(t_game *game)
{
	double	x;
	double	y;

	x = game->player.posX - game->player.dirY * (game->player.moveSpeed / game->player.move_div);
	y = game->player.posY + game->player.dirX * (game->player.moveSpeed / game->player.move_div);
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	// if (enemy_collision(game, x, y))
	//     game_over(game);
}

static void	check_collision(t_game *game, double x, double y)
{
	int	py;
	int	px;

	py = (int)(game->player.posY);
	px = (int)(game->player.posX);
	if (x > game->player.posX && \
	!ft_strchr("1", game->map->lines[py]->content[(int)(x + RADIUS)]))
		game->player.posX = x;
	else if (x < game->player.posX && \
	!ft_strchr("1", game->map->lines[py]->content[(int)(x - RADIUS)]))
		game->player.posX = x;
	if (y > game->player.posY && \
	!ft_strchr("1", game->map->lines[(int)(y + RADIUS)]->content[px]))
		game->player.posY = y;
	else if (y < game->player.posY && \
	!ft_strchr("1", game->map->lines[(int)(y - RADIUS)]->content[px]))
		game->player.posY = y;
}
