//
// Created by delmwin on 9/26/22.
//

# pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "SDL2/SDL.h"

class Game {
public:
    Game();

    // Initialize the game
    bool Initialize();

    // Run game loop until over
    void RunLoop();

    void Shutdown();

    void AddActor(class Actor *actor);

    void RemoveActor(class Actor *actor);

    SDL_Texture *GetTexture(const std::string &filename);

    void AddSprite(class SpriteComponent *sprite);

    void RemoveSprite(class SpriteComponent *sprite);

private:
    // Game related
    std::vector<class Actor *> _actors; // Active actors

    std::vector<class Actor *> _pendingActors; // Pending actors

    std::unordered_map<std::string, SDL_Texture *> _textureMap; // Texture map

    std::vector<class SpriteComponent *> _sprites; // Sprites

    bool _updatingActors; // Is updating actors

    bool _isRunning; // Is the game running

    SDL_Window *_window;
    SDL_Renderer *_renderer;
    Uint32 _ticksCount;

    // Game-specific
    class Ship *_ship; // Player's ship

    // Helper functions for the game loop
    void ProcessInput();

    void UpdateGame();

    void GenerateOutput();

    void LoadData();

    void UnloadData();
};
