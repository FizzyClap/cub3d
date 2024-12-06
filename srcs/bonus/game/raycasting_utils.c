/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:08:10 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:08:12 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	calculate_tex_x_pos(t_game *game, t_ray *ray, t_image **tex);

void	select_wall_texture(t_game *game, t_ray *ray, t_image **tex)
{
	char	pos;

	pos = game->map->lines[(int)game->player.pos_y]->\
	content[(int)game->player.pos_x];
	if (ray->is_door && ray->door_idx == game->door_idx && \
		game->doors[game->door_idx].is_open)
		*tex = doors_animation(game, game->door_idx, game->doors_frames);
	else if (ray->is_door && ray->door_idx == game->door_idx && \
		!game->doors[game->door_idx].is_open)
		*tex = doors_animation(game, game->door_idx, 0);
	else if (ray->is_door && (game->doors[ray->door_idx].is_open || pos == 'D'))
		*tex = &game->door[game->doors_frames - 1];
	else if (ray->is_door && !game->doors[ray->door_idx].is_open)
		*tex = &game->door[0];
	else if (ray->pos_door == 'D')
		select_door_texture(game, ray, tex);
	else if (ray->side == 1 && ray->step_y < 0)
		*tex = &game->texture->image[NORTH];
	else if (ray->side == 1 && ray->step_y > 0)
		*tex = &game->texture->image[SOUTH];
	else if (ray->side == 0 && ray->step_x < 0)
		*tex = &game->texture->image[WEST];
	else if (ray->side == 0 && ray->step_x > 0)
		*tex = &game->texture->image[EAST];
	calculate_tex_x_pos(game, ray, tex);
}

static void	calculate_tex_x_pos(t_game *game, t_ray *ray, t_image **tex)
{
	if (ray->side == 0)
		(*tex)->wall_x = game->player.pos_y + ray->wall_dist * ray->dir_y;
	else
		(*tex)->wall_x = game->player.pos_x + ray->wall_dist * ray->dir_x;
	(*tex)->wall_x -= floor((*tex)->wall_x);
	(*tex)->x = (int)((*tex)->wall_x * (double)(*tex)->width);
	if (ray->side == 0 && ray->dir_x > 0)
		(*tex)->x = (*tex)->width - (*tex)->x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		(*tex)->x = (*tex)->width - (*tex)->x - 1;
}

void	shoot_ray_to_center(t_game *game, bool door)
{
	t_ray	ray;

	init_ray(game, &ray, SCREEN_X / 2);
	calculate_steps(game, &ray);
	if (door == true)
	{
		perform_dda(game, &ray, true);
		if (game->map->lines[ray.door_y]->content[ray.door_x] == 'D')
			toggle_door(game, ray.door_y, ray.door_x);
	}
	else
		game->target = hit_enemy(&ray, game);
}

int	hit_enemy(t_ray *ray, t_game *game)
{
	int		hit;
	int		i;
	char	pos;

	hit = 0;
	ray->map.x = (int)game->player.pos_x;
	ray->map.y = (int)game->player.pos_y;
	while (!hit)
	{
		move_ray(game, ray);
		if (ray->map.y < 0 || ray->map.y >= game->map->y - 1 || \
			ray->map.x < 0 || ray->map.x >= game->map->lines[ray->map.y]->x)
			return (-1);
		pos = game->map->lines[ray->map.y]->content[ray->map.x];
		if (pos == 'A' || pos == '1' || pos == 'D')
			hit = 1;
		i = -1;
		while (++i < game->nb_enemy)
			if ((int)game->enemy[i].x == ray->map.x && \
				(int)game->enemy[i].y == ray->map.y)
				return (i);
	}
	return (-1);
}

void	move_ray(t_game *game, t_ray *ray)
{
	char	pos;

	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_x;
		ray->map.x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_y;
		ray->map.y += ray->step_y;
		ray->side = 1;
	}
	pos = game->map->lines[ray->map.y]->content[ray->map.x];
	ray->pos_door = pos;
	ray->door_x = ray->map.x;
	ray->door_y = ray->map.y;
}
