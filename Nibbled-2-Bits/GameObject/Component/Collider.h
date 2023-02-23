#pragma once
#include "../GameObject.h"
#include "functional"
//penguien is not nesaserry to be a bird
class Collider {
public:
    Play::Point2D m_pos{ 0,0 };
    static int id;
    int m_id = 0;
	GameObject* m_holderInfo = nullptr;
	GameObject* m_opponentInfo = nullptr;
public:
    Collider();
    Collider(Play::Point2D pos);
    virtual ~Collider() {}

    virtual bool collidesWith( Collider& other) = 0;

    virtual void DrawBoundingBox(Play::Colour color = Play::cRed) = 0;

    int Getid();

    bool operator==(Collider& colldier) const;
};

