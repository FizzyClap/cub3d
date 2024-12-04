#include "../includes/cub3D_bonus.h"

static void	data_calcul(t_game *game, t_data *d, t_coord loop);
static void	render(t_game *game, t_data *d, t_coord loop);

void	floor_ceil_raycast(t_game *game)
{
	t_data	d;
	t_coord	loop;

	game->floor_txt = game->door[game->doors_frames + 1];
	game->ceil_txt = game->door[game->doors_frames];
	loop.y = -1;
	while (++loop.y < SCREEN_HEIGHT)
	{
		data_calcul(game, &d, loop);
		loop.x = -1;
		while (++loop.x < SCREEN_WIDTH)
			render(game, &d, loop);
	}
}

static void	data_calcul(t_game *game, t_data *d, t_coord loop)
{
	d->rayDirX0 = game->player.dirX - game->player.planeX;
	d->rayDirY0 = game->player.dirY - game->player.planeY;
	d->rayDirX1 = game->player.dirX + game->player.planeX;
	d->rayDirY1 = game->player.dirY + game->player.planeY;
	d->p = loop.y - SCREEN_HEIGHT / 2;
	d->pos_z = 0.5 * SCREEN_HEIGHT;
	d->row_distance = d->pos_z / d->p;
	d->floor_step_x = d->row_distance * (d->rayDirX1 - d->rayDirX0) / SCREEN_WIDTH;
	d->floor_step_y = d->row_distance * (d->rayDirY1 - d->rayDirY0) / SCREEN_WIDTH;
	d->floor_step_x = d->row_distance * (d->rayDirX1 - d->rayDirX0) / SCREEN_WIDTH;
	d->floor_x = game->player.posX + d->row_distance * d->rayDirX0;
	d->floor_y = game->player.posY + d->row_distance * d->rayDirY0;
}

static void	render(t_game *game, t_data *d, t_coord loop)
{
	d->cell_x = (int)d->floor_x;
	d->cell_y = (int)d->floor_y;
	d->tex_x = (int)(game->floor_txt.width * (d->floor_x - d->cell_x)) % \
		(game->floor_txt.width - 1);
	d->tex_y = (int)(game->floor_txt.height * (d->floor_y - d->cell_y)) % \
		(game->floor_txt.height - 1);
	d->floor_x += d->floor_step_x;
	d->floor_y += d->floor_step_y;
	d->color = game->floor_txt.color[game->floor_txt.width * d->tex_y + d->tex_x];
	my_mlx_pixel_put(&game->raycast, loop.x, loop.y, d->color);
	d->color = game->ceil_txt.color[game->ceil_txt.width * d->tex_y + \
	d->tex_x];
	my_mlx_pixel_put(&game->raycast, loop.x, SCREEN_HEIGHT - loop.y - 1, \
	d->color);
}
