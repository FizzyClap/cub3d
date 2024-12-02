#include "../includes/cub3D_bonus.h"

static void	error_sdl(const char *msg, Mix_Music *music);

void	init_sound(void)
{
	if (SDL_Init(SDL_INIT_AUDIO) == -1)
	{
		SDL_Log("Error: music > %s\n", \
		SDL_GetError());
		SDL_Quit();
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, \
		1024) != 0)
		error_sdl("Error: can't open audio\n", NULL);
}

int	sound(t_game *game)
{
	if (game->launcher_is_running == true)
	{
		game->music->launcher = Mix_LoadMUS("sound/TheBridge.mp3");
		if (!game->music->launcher)
			return (ft_fprintf(2, "Error: Launcher music\n"), FAILURE);
		if (Mix_PlayMusic(game->music->launcher, 0) != 0)
			error_sdl("Error: Launcher music\n", game->music->launcher);
	}
	else if (ft_strcmp(game->map_type, "morgul") == 0)
	{
		game->music->morgul = Mix_LoadMUS("sound/MinasMorgul.mp3");
		if (!game->music->morgul)
			return (ft_fprintf(2, "Error: Morgul music\n"), FAILURE);
		if (Mix_PlayMusic(game->music->morgul, 0) != 0)
			error_sdl("Error: Morgul music\n", game->music->morgul);
	}
	else if (ft_strcmp(game->map_type, "moria") == 0)
	{
		game->music->moria = Mix_LoadMUS("sound/TheBalrogSong.mp3");
		if (!game->music->moria)
			return (ft_fprintf(2, "Error: Moria music\n"), FAILURE);
		if (Mix_PlayMusic(game->music->moria, 0) != 0)
			error_sdl("Error: Moria music\n", game->music->moria);
	}
	return (SUCCESS);
}

static void	error_sdl(const char *msg, Mix_Music *music)
{
	SDL_Log("Error : %s > %s", msg, SDL_GetError());
	if (music != NULL)
		Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
}

void	free_sound(t_game *game)
{
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
	if (game->music->launcher)
		Mix_FreeMusic(game->music->launcher);
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
	if (game->music->gollum)
		Mix_FreeChunk(game->music->gollum);
	if (game->music)
		free(game->music);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	SDL_Quit();
}

int	init_sound_effects(t_game *game)
{
	if (!game->map_type)
		game->music->gollum = Mix_LoadWAV("sound/My Precious.wav");
	else if (ft_strcmp(game->map_type, "morgul") == 0)
	{
		game->music->door = Mix_LoadWAV("sound/harrow.wav");
		game->music->step = Mix_LoadWAV("sound/footstep.wav");
		game->music->weapon = Mix_LoadWAV("sound/fireball.wav");
		game->music->hit = Mix_LoadWAV("sound/firedeath.wav");
		if (!game->music->door || !game->music->step || !game->music->weapon \
		|| !game->music->hit)
			return (ft_fprintf(STDERR_FILENO, "Error: Sound error\n", FAILURE));
	}
	else if (ft_strcmp(game->map_type, "moria") == 0)
	{
		game->music->door = Mix_LoadWAV("sound/ancientdoor.wav");
		game->music->step = Mix_LoadWAV("sound/balrogstep.wav");
		game->music->weapon = Mix_LoadWAV("sound/whip.wav");
		game->music->hit = Mix_LoadWAV("sound/hit.wav");
		if (!game->music->door || !game->music->step || !game->music->weapon \
		|| !game->music->hit)
			return (ft_fprintf(STDERR_FILENO, "Error: Sound error\n", FAILURE));
	}
	return (SUCCESS);
}

void	struct_game_sound(t_game *game)
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
}
