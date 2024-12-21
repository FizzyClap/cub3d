/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:05:20 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:05:22 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	free_music(t_game *game);

int	close_game(t_game *game)
{
	free_image(game);
	free_launcher_image(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_texture(game->texture);
	free_map(game->map);
	free_sound(game);
	free(game->player.action);
	free(game->enemy);
	free(game->doors);
	free(game->weapon);
	free(game->door);
	free(game);
	exit(EXIT_SUCCESS);
}

int	close_launcher(t_game *game)
{
	free_launcher_image(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free(game->map);
	free_sound(game);
	free(game);
	exit(EXIT_SUCCESS);
}

void	free_sound(t_game *game)
{
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
	free_music(game);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	SDL_Quit();
}

static void	free_music(t_game *game)
{
	if (game->music->launcher)
		Mix_FreeMusic(game->music->launcher);
	if (game->music->gollum_song)
		Mix_FreeMusic(game->music->gollum_song);
	if (game->music->gollum)
		Mix_FreeChunk(game->music->gollum);
	if (game->music->moria)
		Mix_FreeMusic(game->music->moria);
	if (game->music->morgul)
		Mix_FreeMusic(game->music->morgul);
	if (game->music->door)
		Mix_FreeChunk(game->music->door);
	if (game->music->step)
		Mix_FreeChunk(game->music->step);
	if (game->music->weapon)
		Mix_FreeChunk(game->music->weapon);
	if (game->music->hit)
		Mix_FreeChunk(game->music->hit);
	if (game->music->game_over)
		Mix_FreeMusic(game->music->game_over);
	if (game->music)
		free(game->music);
}
