//
// Created by delmwin on 9/26/22.
//

#include "Component.h"
#include "Actor.h"

Component::Component(struct Actor *owner, int updateOrder) : _owner(owner), _updateOrder(updateOrder) {
    // Add to Actors component list
    _owner->AddComponent(this);
}

Component::~Component() {
    _owner->RemoveComponent(this);
}

void Component::Update(float deltaTime) {

}

void Component::ProcessInput(const uint8_t *keyState) {

}
