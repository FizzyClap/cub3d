/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:07:48 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:07:49 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	is_color_close_to_magenta(int color, int tolerance);

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > SCREEN_X || y > SCREEN_Y)
		return ;
	if (is_color_close_to_magenta(color, 100) == FAILURE)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	my_put_image(t_game *game, t_image *img, int x_offset, int y_offset)
{
	t_coord	pos;
	int		color;
	char	*pixel;
	int		pixel_offset;
	int		total_size;

	pos.y = -1;
	while (++pos.y < img->height)
	{
		pos.x = -1;
		while (++pos.x < img->width)
		{
			pixel_offset = pos.y * img->line_len + pos.x * (img->bpp / 8);
			total_size = img->height * img->line_len;
			if (pixel_offset >= total_size)
				return ;
			pixel = img->addr + pixel_offset;
			color = *(int *)pixel;
			my_mlx_pixel_put(&game->raycast, pos.x + x_offset, \
			pos.y + y_offset, color);
		}
	}
}

static int	is_color_close_to_magenta(int color, int tolerance)
{
	t_color	magenta;
	t_color	col;

	col.r = (color >> 16) & 0xFF;
	col.g = (color >> 8) & 0xFF;
	col.b = color & 0xFF;
	magenta.r = 0xFC;
	magenta.g = 0x00;
	magenta.b = 0xFF;
	if (abs(col.r - magenta.r) <= tolerance && \
		abs(col.g - magenta.g) <= tolerance && \
		abs(col.b - magenta.b) <= tolerance)
		return (FAILURE);
	return (SUCCESS);
}

int	load_xpm(t_game *game, t_image *texture, char *xpm_file)
{
	int	width;
	int	height;

	texture->img = mlx_xpm_file_to_image(game->mlx, xpm_file, &width, &height);
	if (!texture->img)
		return (FAILURE);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, \
		&texture->line_len, &texture->endian);
	texture->color = (int *)texture->addr;
	texture->width = width;
	texture->height = height;
	return (SUCCESS);
}

int	mouse_click(int button, int x, int y, t_game *game)
{
	(void)button;
	if (x >= 890 && x <= 1000 && y >= 50 && y <= 170 && !Mix_Playing(-1))
		game->show_gollum = true;
	else if (x >= 140 && x <= 700 && y >= 415 && y <= 755)
	{
		game->file = "maps/moria_bonus.cub";
		free_launcher_image(game);
		if (!create_launcher_images(game, "textures/launcher/launcher_moria"))
			return (FAILURE);
	}
	else if (x >= 1220 && x <= 1785 && y >= 420 && y <= 750)
	{
		game->file = "maps/morgul_bonus.cub";
		free_launcher_image(game);
		if (!create_launcher_images(game, "textures/launcher/launcher_morgul"))
			return (FAILURE);
	}
	else
	{
		game->file = NULL;
		free_launcher_image(game);
		if (!create_launcher_images(game, "textures/launcher/launcher"))
			return (FAILURE);
	}
	return (SUCCESS);
}
