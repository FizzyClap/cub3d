#include "../includes/cub3D_bonus.h"

double	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec + time.tv_usec / 1000000.0);
}

void	kill_enemy(t_game *game)
{
	t_coord	pos;
	int		target;

	target = game->target;
	if (target != -1)
	{
		pos.y = (int)game->enemy[target].y;
		pos.x = (int)game->enemy[target].x;
		Mix_PlayChannel(-1, game->music->hit, 0);
		game->enemy[target].is_animating = true;
		game->enemy[target].start_animation = get_current_time();
	}
}

void	destroy_enemy(t_game *game, int target, t_coord pos)
{
	int	i;

	i = -1;
	while (++i < game->enemy_frames)
	{
		if (game->enemy[target].texture[i].img)
			mlx_destroy_image(game->mlx, game->enemy[target].texture[i].img);
		game->enemy[target].texture[i].img = NULL;
		game->enemy[target].x = -1;
		game->enemy[target].y = -1;
	}
	game->map->lines[pos.y]->content[pos.x] = '0';
}