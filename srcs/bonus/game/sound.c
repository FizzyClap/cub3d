#include "../includes/cub3D_bonus.h"

void	init_sound(void)
{
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
}

int	sound(t_game *game)
{
	if (game->launcher_is_running == true)
	{
		game->music->launcher = Mix_LoadMUS("sound/TheBridge.mp3");
		Mix_PlayMusic(game->music->launcher, -1);
		game->music->gollum = Mix_LoadWAV("sound/My_Precious.wav");
		game->music->gollum_song = Mix_LoadMUS("sound/Gollum's song.mp3");
		if (!game->music->gollum || !game->music->launcher)
			return (ft_fprintf(STDERR_FILENO, "Error: Sound error\n"), FAILURE);
	}
	else if (ft_strcmp(game->map_type, "morgul") == 0)
	{
		game->music->morgul = Mix_LoadMUS("sound/MinasMorgul.mp3");
		if (!game->music->morgul)
			return (ft_fprintf(2, "Error: Morgul music\n"), FAILURE);
		Mix_PlayMusic(game->music->morgul, -1);
	}
	else if (ft_strcmp(game->map_type, "moria") == 0)
	{
		game->music->moria = Mix_LoadMUS("sound/TheBalrogSong.mp3");
		if (!game->music->moria)
			return (ft_fprintf(2, "Error: Moria music\n"), FAILURE);
		Mix_PlayMusic(game->music->moria, -1);
	}
	return (SUCCESS);
}

int	init_sound_effects(t_game *game)
{
	if (ft_strcmp(game->map_type, "morgul") == 0)
	{
		game->music->door = Mix_LoadWAV("sound/harrow.wav");
		game->music->step = Mix_LoadWAV("sound/footstep.wav");
		game->music->weapon = Mix_LoadWAV("sound/fireball.wav");
		game->music->hit = Mix_LoadWAV("sound/nazgul.wav");
		game->music->game_over = Mix_LoadMUS("sound/Gandalf's fall.mp3");
		if (!game->music->door || !game->music->step || !game->music->weapon \
		|| !game->music->hit || !game->music->game_over)
			return (ft_fprintf(STDERR_FILENO, "Error: Sound error\n", FAILURE));
	}
	else if (ft_strcmp(game->map_type, "moria") == 0)
	{
		game->music->door = Mix_LoadWAV("sound/ancientdoor.wav");
		game->music->step = Mix_LoadWAV("sound/balrogstep.wav");
		game->music->weapon = Mix_LoadWAV("sound/whip.wav");
		game->music->hit = Mix_LoadWAV("sound/hit.wav");
		game->music->game_over = Mix_LoadMUS("sound/ShallNotPass.mp3");
		if (!game->music->door || !game->music->step || !game->music->weapon \
		|| !game->music->hit || !game->music->game_over)
			return (ft_fprintf(STDERR_FILENO, "Error: Sound error\n", FAILURE));
	}
	return (SUCCESS);
}

void	init_struct_game_sound(t_game *game)
{
	game->music = malloc(sizeof(t_music));
	if (!game->music)
		return ;
	game->music->launcher = NULL;
	game->music->moria = NULL;
	game->music->morgul = NULL;
	game->music->door = NULL;
	game->music->step = NULL;
	game->music->weapon = NULL;
	game->music->hit = NULL;
	game->music->gollum = NULL;
	game->music->game_over = NULL;
	game->music->gollum_song = NULL;
	game->restart_music = false;
	game->show_gollum = false;
	game->nb_gollum = 0;
	game->gollum_time = DBL_MAX;
}

void	free_sound(t_game *game)
{
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
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
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	SDL_Quit();
}
