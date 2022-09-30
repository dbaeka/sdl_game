//
// Created by delmwin on 9/26/22.
//

#pragma once

class Component {
public:
    explicit Component(class Actor *owner, int updateOrder = 100);

    virtual ~Component();

    virtual void Update(float deltaTime);

    int GetUpdateOrder() const { return _updateOrder; }

protected:
    class Actor *_owner;

    int _updateOrder;
};