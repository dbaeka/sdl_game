//
// Created by delmwin on 9/26/22.
//

#pragma once

#include <vector>
#include <GameMath.h>
#include <cstdint>

class Actor {
public:
    // Track State of Actor
    enum State {
        EActive, EPaused, EDead, EInvisible
    };

    explicit Actor(class Game *game);

    virtual ~Actor();

    // Update called from Game
    void Update(float deltaTime);

    // Update all components attached to Actor
    void UpdateComponents(float deltaTime);

    // Actor-Specific Update
    virtual void UpdateActor(float deltaTime);

    // Process Input called from Game Class
    void ProcessInput(const uint8_t *keyState);

    // Overridable input handling for actor
    virtual void ActorInput(const uint8_t *keyState);

    // Getters/Setters
    State GetState() const { return _state; }

    void SetState(State state) { _state = state; }

    const Vector2 &GetPosition() const { return _position; }

    void SetPosition(const Vector2 &position) { _position = position; }

    float GetScale() const { return _scale; }

    void SetScale(float scale) { _scale = scale; }

    float GetRotation() const { return _rotation; }

    void SetRotation(float rotation) { _rotation = rotation; }

    Vector2 GetForward() const;

    Game *GetGame() const { return _game; }

    // Add/Remove Component
    void AddComponent(class Component *component);

    void RemoveComponent(class Component *component);

private:
    State _state;

    // Transform
    Vector2 _position; // Center position of actor

    float _scale; // 0 to 1.0

    float _rotation; // Angle of rotation (radians)

    std::vector<class Component *> _components;

    class Game *_game;
};