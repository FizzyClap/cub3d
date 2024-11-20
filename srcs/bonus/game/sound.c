#include "../includes/cub3D.h"

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

void	sound(t_game *game)
{
	init_sound();
	if (game->launcher_is_running == true)
	{
		game->music->launcher = Mix_LoadMUS("sound/TheBridge.mp3");
		if (!game->music->launcher)
			error_sdl("Error: Launcher music\n", game->music->launcher);
		if (Mix_PlayMusic(game->music->launcher, 0) != 0)
			error_sdl("Error: Launcher music\n", game->music->launcher);
	}
	else if (ft_strcmp(game->file, "maps/morgul.cub") == 0)
	{
		game->music->morgul = Mix_LoadMUS("sound/MinasMorgul.mp3");
		if (!game->music->morgul)
			error_sdl("Error: Morgul music\n", game->music->morgul);
		if (Mix_PlayMusic(game->music->morgul, 0) != 0)
			error_sdl("Error: Morgul music\n", game->music->morgul);
	}
	else if (ft_strcmp(game->file, "maps/moria.cub") == 0)
	{
		game->music->moria = Mix_LoadMUS("sound/TheBalrogSong.mp3");
		if (!game->music->moria)
			error_sdl("Error: Moria music\n", game->music->moria);
		if (Mix_PlayMusic(game->music->moria, 0) != 0)
			error_sdl("Error: Moria music\n", game->music->moria);
	}
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
	if (game->music->launcher)
		Mix_FreeMusic(game->music->launcher);
	if (game->music->moria)
		Mix_FreeMusic(game->music->moria);
	if (game->music->morgul)
		Mix_FreeMusic(game->music->morgul);
	if (game->music->door)
		Mix_FreeChunk(game->music->door);
	if (game->music)
		free(game->music);
	Mix_CloseAudio();
	SDL_Quit();
}

void	init_sound_effects(t_game *game)
{
	if (ft_strcmp(game->file, "maps/morgul.cub") == 0)
	{
		game->music->door = Mix_LoadWAV("sound/harrow.wav");
		if (!game->music->door)
			error_sdl("Error: Door chunk\n", NULL);
	}
	if (ft_strcmp(game->file, "maps/moria.cub") == 0)
	{
		game->music->door = Mix_LoadWAV("sound/ancientdoor.wav");
		if (!game->music->door)
			error_sdl("Error: Door chunk\n", NULL);
		game->music->step = Mix_LoadWAV("sound/balrogstep.wav");
		if (!game->music->door)
			error_sdl("Error: Step chunk\n", NULL);
	}
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
}
