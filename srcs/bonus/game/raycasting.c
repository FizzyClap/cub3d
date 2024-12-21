/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:08:19 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:16:14 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	draw_wall(t_game *game, t_ray *ray, t_coord loop);

void	raycasting(t_game *game)
{
	t_coord	loop;
	t_ray	*ray;
	t_list	*tmp;

	floor_and_ceiling(game);
	ray = ft_calloc(sizeof(t_ray), 1);
	if (!ray)
		return ;
	loop.x = -1;
	while (++loop.x < SCREEN_X)
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

	pos.x = (int)game->player.pos_x;
	pos.y = (int)game->player.pos_y;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - pos.x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (pos.x + 1.0 - game->player.pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - pos.y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (pos.y + 1.0 - game->player.pos_y) * ray->delta_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray, bool hitDoor)
{
	int		hit;
	bool	is_last_door;
	bool	is_first;
	char	pos;
	char	player_pos;

	hit = 0;
	is_last_door = false;
	is_first = true;
	ray->map.x = (int)game->player.pos_x;
	ray->map.y = (int)game->player.pos_y;
	while (!hit)
	{
		move_ray(game, ray);
		pos = game->map->lines[ray->map.y]->content[ray->map.x];
		player_pos = game->map->lines[(int)game->player.pos_y]->\
		content[(int)game->player.pos_x];
		if (pos == '1' || (pos == 'D' && hitDoor == true))
			hit = 1;
		else if (pos == 'D' || is_last_door || (is_first && player_pos == 'D'))
			add_doors(game, ray, &is_last_door, &is_first);
		is_first = false;
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->delta_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->delta_y);
}

static void	draw_wall(t_game *game, t_ray *ray, t_coord loop)
{
	t_image	*tex;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	line_height = (int)(SCREEN_Y / ray->wall_dist);
	draw_start = -line_height / 2 + SCREEN_Y / 2;
	draw_end = line_height / 2 + SCREEN_Y / 2;
	select_wall_texture(game, ray, &tex);
	tex->step = 1.0 * tex->height / line_height;
	tex->pos = (draw_start - SCREEN_Y / 2 + line_height / 2) * tex->step;
	loop.y = draw_start - 1;
	game->z_buffer[loop.x] = ray->wall_dist;
	while (++loop.y < draw_end)
	{
		tex->y = (int)tex->pos % (tex->height - 1);
		tex->pos += tex->step;
		color = tex->color[tex->height * tex->y + tex->x];
		my_mlx_pixel_put(&game->raycast, loop.x, loop.y + game->player.z, \
			color);
	}
}
