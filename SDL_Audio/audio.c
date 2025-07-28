#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <stdio.h>

int main()
{
    SDL_AudioSpec spec;  
    Uint8 *audio_buf;    
    Uint32 audio_len;
    
    SDL_InitSubSystem(SDL_INIT_AUDIO);

    SDL_AudioSpec *return_spec = SDL_LoadWAV("sample.wav", &spec, &audio_buf, &audio_len);

    if (return_spec == NULL)
    {
        fprintf(stderr, "Error loading WAV file: %s\n", SDL_GetError());
        return 1;
    }
    else
    {
        printf("WAV file loaded successfully.\n");
    }

    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
    printf("device id %d\n", dev);

    int res = SDL_QueueAudio(dev, audio_buf, audio_len);
    if(res == 0)
    {
        printf("Audio queued successfully.\n");
        SDL_PauseAudioDevice(dev, 0);  
        SDL_Delay(5000);  
    }
    else
    {
        fprintf(stderr, "Error queuing audio: %s\n", SDL_GetError());
    }

    
    SDL_FreeWAV(audio_buf);
    SDL_CloseAudioDevice(dev);
    SDL_Quit();
    return 0;
}