/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:08:52 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:08:54 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static t_ray	*dup_ray(t_game *game, t_ray *ray);

void	draw_doors(t_game *game, t_ray *ray, t_coord loop)
{
	t_image	*tex;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	calculate_wall_distance(ray);
	if (ray->wall_dist > RADIUS / 2)
	{
		line_height = (int)(SCREEN_Y / ray->wall_dist);
		draw_start = -line_height / 2 + SCREEN_Y / 2;
		draw_end = line_height / 2 + SCREEN_Y / 2;
		select_wall_texture(game, ray, &tex);
		tex->step = 1.0 * tex->height / line_height;
		tex->pos = (draw_start - SCREEN_Y / 2 + line_height / 2) * tex->step;
		loop.y = draw_start - 1;
		while (++loop.y < draw_end)
		{
			tex->y = (int)tex->pos % (tex->height - 1);
			tex->pos += tex->step;
			color = tex->color[tex->height * tex->y + tex->x];
			my_mlx_pixel_put(&game->raycast, loop.x, loop.y + game->player.z, \
			color);
		}
	}
}

void	doors_transparency(t_game *game, t_list **tmp, t_ray *ray, t_coord loop)
{
	*tmp = ray->doors;
	while (*tmp)
	{
		draw_doors(game, (*tmp)->content, loop);
		*tmp = (*tmp)->next;
	}
	ft_lstclear(&ray->doors, free);
	ray->doors = NULL;
}

void	add_doors(t_game *game, t_ray *ray, bool *is_last_door, bool *is_first)
{
	t_ray	*transparency;

	transparency = dup_ray(game, ray);
	if (*is_last_door == true || *is_first == true)
		transparency->is_door = true;
	ft_lstadd_front(&ray->doors, ft_lstnew(transparency));
	*is_last_door = !*is_last_door;
	if (*is_first && ray->pos_door != 'D')
		*is_last_door = false;
}

static t_ray	*dup_ray(t_game *game, t_ray *ray)
{
	t_ray	*dest;
	int		i;

	dest = ft_calloc(sizeof(t_ray), 1);
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < game->nb_doors)
	{
		if (game->doors[i].x == ray->door_x && \
			game->doors[i].y == ray->door_y)
			ray->door_idx = i;
	}
	ft_memcpy(dest, ray, sizeof(t_ray));
	dest->doors = NULL;
	return (dest);
}
