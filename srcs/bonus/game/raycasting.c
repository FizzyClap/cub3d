#include "../includes/cub3D_bonus.h"

void	draw_wall(t_game *game, t_ray *ray, t_coord loop);

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->pos_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->dir_x = game->player.dirX + game->player.planeX * ray->pos_x;
	ray->dir_y = game->player.dirY + game->player.planeY * ray->pos_x;
	if (ray->dir_x == 0)
		ray->delta_x = INT_MAX;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = INT_MAX;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}

void	raycasting(t_game *game)
{
	t_coord	loop;
	t_ray	*ray;
	t_list	*tmp;

	floor_ceil_raycast(game);
	ray = ft_calloc(sizeof(t_ray), 1);
	if (!ray)
		return ;
	loop.x = -1;
	while (++loop.x < SCREEN_WIDTH)
	{
		init_ray(game, ray, loop.x);
		calculate_steps(game, ray);
		perform_dda(game, ray, false);
		calculate_wall_distance(ray);
		draw_wall(game, ray, loop);
		doors_transparency(game, &tmp, ray, loop);
	}
	sort_enemies(game);
	render_enemies(game);
	free(ray);
}

void	calculate_steps(t_game *game, t_ray *ray)
{
	t_coord	pos;

	pos.x = (int)game->player.posX;
	pos.y = (int)game->player.posY;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.posX - pos.x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (pos.x + 1.0 - game->player.posX) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.posY - pos.y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (pos.y + 1.0 - game->player.posY) * ray->delta_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray, bool hitDoor)
{
	int		hit;
	bool	isLastDoor;
	bool	isFirst;
	char	pos;

	hit = 0;
	isLastDoor = false;
	isFirst = true;
	ray->map.x = (int)game->player.posX;
	ray->map.y = (int)game->player.posY;
	while (!hit)
	{
		move_ray(game, ray);
		pos = game->map->lines[ray->map.y]->content[ray->map.x];
		if (pos == '1' || (pos == 'D' && hitDoor == true))
			hit = 1;
		else if (pos == 'D' || isLastDoor || (isFirst && game->map->lines[(int)game->player.posY]->content[(int)game->player.posX] == 'D'))
			add_doors(game, ray, &isLastDoor, &isFirst);
		isFirst = false;
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->delta_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->delta_y);
}

void	draw_wall(t_game *game, t_ray *ray, t_coord loop)
{
	t_image	*tex;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	line_height = (int)(SCREEN_HEIGHT / ray->wall_dist);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	select_wall_texture(game, ray, &tex);
	tex->step = 1.0 * tex->height / line_height;
	tex->pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * tex->step;
	loop.y = draw_start - 1;
	game->z_buffer[loop.x] = ray->wall_dist;
	while (++loop.y < draw_end)
	{
		tex->y = (int)tex->pos % (tex->height - 1);
		tex->pos += tex->step;
		color = tex->color[tex->height * tex->y + tex->x];
		my_mlx_pixel_put(&game->raycast, loop.x, loop.y, color);
	}
}
