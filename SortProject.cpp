#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <random>
#include <ranges>

using namespace std;
void draw_state(vector<int> &sorting, SDL_Renderer *renderer, long pinkx, long pink)
{
    int xAxis = 0;
    for (int i : sorting)
    {
        if (xAxis == pink && xAxis < 99)
        {
            SDL_SetRenderDrawColor(renderer, 220, 0, 180, 255);
        }
        else if (xAxis == pinkx && xAxis < 99)
        {
            SDL_SetRenderDrawColor(renderer, 220, 0, 180, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        }
        SDL_RenderDrawLine(renderer, xAxis, 100, xAxis, i);
        // Mix_PlayChannel(-1, soundEffect, 0);
        xAxis += 1;
    }
}

void draw_finished_state(vector<int> &sorting, SDL_Renderer *renderer, int index)
{
    int xAxis = 0;
    for (int i : sorting)
    {
        if (xAxis <= index)
        {
            SDL_SetRenderDrawColor(renderer, 220, 0, 180, 255);
            SDL_RenderDrawLine(renderer, xAxis, 100, xAxis, i);
        }
        else if (xAxis > index)
        {
            SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
            SDL_RenderDrawLine(renderer, xAxis, 100, xAxis, i);
        }
        xAxis += 1;
    }
}

int main()
{
    random_device random;
    uniform_int_distribution<int> dis(1, 99);
    vector<int> randomNumbers;
    SDL_INIT_AUDIO;
    // if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 < 0)) {
    //     cout << "Error: " << Mix_GetError() << endl;
    // }
    // Mix_Chunk *soundEffect = Mix_LoadWAV("blip.wav");
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(1000, 800, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 8);
    // SDL_PumpEvents();
    SDL_WaitEvent(0);

    for (int i = 0; i < 100; i++)
    {
        randomNumbers.push_back(dis(random));
    }
    for (int i = 0; i < randomNumbers.size(); i++)
    {
        for (int j = i; j < randomNumbers.size(); j++)
        {
            if (randomNumbers[j] > randomNumbers[i])
            {
                swap(randomNumbers[j], randomNumbers[i]);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(randomNumbers, renderer, i, j);
            SDL_RenderPresent(renderer);
            // SDL_Delay(1);
        }
    }

    int count = 0;
    for (int i : randomNumbers)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_finished_state(randomNumbers, renderer, count);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
        count++;
    }

    SDL_Delay(2000);
    // Mix_FreeChunk(soundEffect);
    // soundEffect = nullptr;
    // Mix_CloseAudio();
}