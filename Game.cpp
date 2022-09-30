//
// Created by delmwin on 9/26/22.
//

#include "Game.h"
#include <algorithm>
#include "Actor.h"
#include "SDL2/SDL_image.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BGSpriteComponent.h"

Game::Game() :
        _isRunning(true),
        _updatingActors(false),
        _window(nullptr),
        _ticksCount(0),
        _ship(nullptr),
        _renderer(nullptr) {
}

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    _window = SDL_CreateWindow("Core Concepts", 100, 100, 1024, 768, 0);
    if (!_window) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return false;
    }

    _ticksCount = SDL_GetTicks();

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    LoadData();

    return true;
}

void Game::RunLoop() {
    while (_isRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown() {
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                _isRunning = false;
                break;
        }
    }

    const Uint8 *keys_state = SDL_GetKeyboardState(nullptr);
    if (keys_state[SDL_SCANCODE_ESCAPE]) {
        _isRunning = false;
    }

    // Process ship input
    _ship->ProcessKeyboard(keys_state);
}

void Game::UpdateGame() {
    // Frame Limit to 16ms for 60fps using 1/60f = 16ms interval between frames
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), _ticksCount + 16));

    float deltaTime = (float) (SDL_GetTicks() - _ticksCount) / 1000.0f;
    deltaTime = std::fmin(deltaTime, 0.05f); // Bound max delta time to

    // Update all actors
    _updatingActors = true;

    for (auto actor: _actors) {
        actor->Update(deltaTime);
    }

    _updatingActors = false;

    // Move any pending actor to _actors
    for (auto pending: _pendingActors) {
        _actors.emplace_back(pending);
    }
    _pendingActors.clear();

    // Remove Dead Actors
    std::vector<Actor *> deadActors;

    for (auto actor: _actors) {
        if (actor->GetState() == Actor::EDead) {
            deadActors.emplace_back(actor);
        }
    }

    for (auto actor: deadActors) {
        delete actor;
    }
}

void Game::GenerateOutput() {
    // Set bg color for clear
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

    // Clear back buffer with bg color
    SDL_RenderClear(_renderer);

    for (auto sprite: _sprites) {
        sprite->Draw(_renderer);
    }

    SDL_RenderPresent(_renderer);
}

void Game::AddActor(Actor *actor) {
    if (_updatingActors) {
        _pendingActors.emplace_back(actor);
    } else {
        _actors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor *actor) {
    // Check respective actors list
    auto iter = std::find(_pendingActors.begin(), _pendingActors.end(), actor);

    if (iter != _pendingActors.end()) {
        // Swamp with last elem and pop off
        std::iter_swap(iter, _pendingActors.end() - 1);
        _pendingActors.pop_back();
    }

    iter = std::find(_actors.begin(), _actors.end(), actor);

    if (iter != _actors.end()) {
        // Swamp with last elem and pop off
        std::iter_swap(iter, _actors.end() - 1);
        _actors.pop_back();
    }
}

SDL_Texture *Game::GetTexture(const std::string &filename) {
    SDL_Texture *texture = nullptr;
    auto iter = _textureMap.find(filename);
    if (iter != _textureMap.end()) {
        texture = iter->second;
    } else {
        // Load from file
        SDL_Surface *surface = IMG_Load(filename.c_str());
        if (!surface) {
            SDL_Log("Couldn't load texture file %s", filename.c_str());
            return nullptr;
        }
        // Create texture from surface
        texture = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_FreeSurface(surface);
        if (!texture) {
            SDL_Log("Unable to create texture from surface for %s", filename.c_str());
            return nullptr;
        }
        _textureMap.emplace(filename.c_str(), texture);
    }
    return texture;
}

void Game::LoadData() {
    _ship = new Ship(this);
    _ship->SetPosition(Vector2(100.0f, 384.0f));
    _ship->SetScale(1.5f);

    auto screenSize = Vector2{1024.0, 768.0f};

    // BG Actor
    auto *temp = new Actor(this);
    temp->SetPosition(Vector2(screenSize.x / 2, screenSize.y / 2));

    // Back BG Layer
    auto *bg = new BGSpriteComponent(temp);
    bg->SetScreenSize(screenSize);
    std::vector<SDL_Texture *> bgTextures = {
            GetTexture("Assets/ShipGame/Farback01.png"),
            GetTexture("Assets/ShipGame/Farback02.png")
    };
    bg->SetBGTextures(bgTextures);
    bg->SetScrollSpeed(-100.0f);

    // Create Front BG Layer
    bg = new BGSpriteComponent(temp, 50);
    bg->SetScreenSize(screenSize);
    bgTextures = {
            GetTexture("Assets/ShipGame/Stars.png"),
            GetTexture("Assets/ShipGame/Stars.png")
    };
    bg->SetBGTextures(bgTextures);
    bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData() {
    while (!_actors.empty()) {
        delete _actors.back();
    }

    for (const auto &i: _textureMap) {
        SDL_DestroyTexture((i.second));
    }
    _textureMap.clear();
}

void Game::AddSprite(class SpriteComponent *sprite) {
    int drawOrder = sprite->GetDrawOrder();

    auto iter = _sprites.begin();
    for (; iter != _sprites.end(); ++iter) {
        if (drawOrder < (*iter)->GetDrawOrder()) {
            break;
        }
    }

    // Insert elem before iter
    _sprites.insert(iter, sprite);
}

void Game::RemoveSprite(struct SpriteComponent *sprite) {
    // No swapping because of ordering
    auto iter = std::find(_sprites.begin(), _sprites.end(), sprite);
    _sprites.erase(iter);
}
