#pragma once
class Collider {
public:
    Collider() {}
    virtual ~Collider() {}

    virtual bool collidesWith(const Collider& other) const = 0;
};

class BoxCollider : public Collider {
public:
    BoxCollider(float width, float height) : m_width(width), m_height(height) {}

    bool collidesWith(const Collider& other) const override;

private:
    float m_width, m_height;
};


class CircleCollider : public Collider {
public:
    CircleCollider(float radius) : m_radius(radius) {}

    bool collidesWith(const Collider& other) const override;

private:
    float m_radius;
};


