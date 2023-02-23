#pragma once
#include "ConsumableObj.h"

enum class E_TRAPCOLOR
{
	DARK_WOOD,
	LIGHT_WOOD
};

class MouseTrap:public ConsumableObj
{

private:
	E_TRAPCOLOR m_color { E_TRAPCOLOR::DARK_WOOD };
	bool isActived = false;
public:
	MouseTrap(Play::Point2D pos, E_TRAPCOLOR color = E_TRAPCOLOR::DARK_WOOD);
	~MouseTrap();

	void SetColor(E_TRAPCOLOR color);

	void SetActive(bool active);

	void OnColorChange();

	void Update() override;
	void Render() override;
	
};

