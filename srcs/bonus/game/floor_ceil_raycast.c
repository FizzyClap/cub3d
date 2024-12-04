#include "../includes/cub3D_bonus.h"

static void	floor_calcul(t_game *game, t_data *d, t_coord loop);
static void	render(t_game *game, t_data *d, t_coord loop, t_image texture);
static void	ceil_calcul(t_game *game, t_data *d, t_coord loop);

void	floor_raycast(t_game *game)
{
	t_data	d;
	t_coord	loop;
	t_image	floor_texture;

	floor_texture = game->door[game->doors_frames + 1];
	loop.y = SCREEN_HEIGHT / 2 + game->player.z - 1;
	while (++loop.y < SCREEN_HEIGHT)
	{
		floor_calcul(game, &d, loop);
		loop.x = -1;
		while (++loop.x < SCREEN_WIDTH)
			render(game, &d, loop, floor_texture);
	}
}

void	ceil_raycast(t_game *game)
{
	t_data	d;
	t_coord	loop;
	t_image	ceil_texture;

	ceil_texture = game->door[game->doors_frames];
	loop.y = -1;
	while (++loop.y < SCREEN_HEIGHT / 2 + game->player.z)
	{
		ceil_calcul(game, &d, loop);
		loop.x = -1;
		while (++loop.x < SCREEN_WIDTH)
			render(game, &d, loop, ceil_texture);
	}

}

static void	floor_calcul(t_game *game, t_data *d, t_coord loop)
{
	d->rayDirX0 = game->player.dirX - game->player.planeX;
	d->rayDirY0 = game->player.dirY - game->player.planeY;
	d->rayDirX1 = game->player.dirX + game->player.planeX;
	d->rayDirY1 = game->player.dirY + game->player.planeY;
	d->p = loop.y - SCREEN_HEIGHT / 2 - game->player.z;
	d->pos_z = 0.5 * SCREEN_HEIGHT;
	d->row_distance = d->pos_z / d->p;
	d->floor_step_x = d->row_distance * (d->rayDirX1 - d->rayDirX0) / SCREEN_WIDTH;
	d->floor_step_y = d->row_distance * (d->rayDirY1 - d->rayDirY0) / SCREEN_WIDTH;
	d->floor_x = game->player.posX + d->row_distance * d->rayDirX0;
	d->floor_y = game->player.posY + d->row_distance * d->rayDirY0;
}

static void	ceil_calcul(t_game *game, t_data *d, t_coord loop)
{
	d->rayDirX0 = game->player.dirX - game->player.planeX;
	d->rayDirY0 = game->player.dirY - game->player.planeY;
	d->rayDirX1 = game->player.dirX + game->player.planeX;
	d->rayDirY1 = game->player.dirY - game->player.planeY;
	d->p = loop.y - SCREEN_HEIGHT / 2 + game->player.z;
	d->pos_z = 0.5 * SCREEN_HEIGHT;
	d->row_distance = d->pos_z / d->p;
	d->floor_step_x = d->row_distance * (d->rayDirX1 - d->rayDirX0) / SCREEN_WIDTH;
	d->floor_step_y = d->row_distance * (d->rayDirY1 - d->rayDirY0) / SCREEN_WIDTH;
	d->floor_x = game->player.posX + d->row_distance * d->rayDirX0;
	d->floor_y = game->player.posY + d->row_distance * d->rayDirY0;
}

static void	render(t_game *game, t_data *d, t_coord loop, t_image texture)
{
	d->cell_x = (int)d->floor_x;
	d->cell_y = (int)d->floor_y;
	d->tex_x = (int)(texture.width * (d->floor_x - d->cell_x)) % \
		(texture.width - 1);
	d->tex_y = (int)(texture.height * (d->floor_y - d->cell_y)) % \
		(texture.height - 1);
	d->floor_x += d->floor_step_x;
	d->floor_y += d->floor_step_y;
	d->color = texture.color[texture.width * d->tex_y + d->tex_x];
	my_mlx_pixel_put(&game->raycast, loop.x, loop.y, d->color);
}
