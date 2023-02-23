#pragma once
#include "ConsumableObj.h"
class Cheese:public ConsumableObj
{

private:

public:
	Cheese(Play::Point2D pos);
	~Cheese();

	void Update() override;
	void Render() override;


};
