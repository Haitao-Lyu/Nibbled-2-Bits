#pragma once
#include "GameObject.h"
#include "../GameTool/Timer.h"
#include "MouseState.h"
enum class E_MOUSE_STATE
{
	idleState,
	walkState,
	runState,
	jumpState,
	hurtState,
	whackedState,
	dieState,
};

enum class E_MOUSE_COLOR
{
	DARK_GREY,
	GREY,
	WHITE,
};

class Mouse:public GameObject
{
	friend class MouseState		;
	friend class MouseRunState	;
	friend class MouseDieState	;
	friend class MouseIdleState	;
	friend class MouseJumpState	;
	friend class MouseWalkState	;
	friend class MouseHurtState	;
	friend class MouseWhackedState;
private:
	const char* c_darkGrey = "_dark_grey_";
	const char* c_grey = "_grey_";
	const char* c_white = "_white_";
	const char* m_Color;
	float m_scale = 0.3f;
	MouseState* m_state;
	MouseRunState*	   runState		;
	MouseDieState*	   dieState		;
	MouseIdleState*	   idleState	;
	MouseJumpState*	   jumpState	;
	MouseWalkState*	   walkState	;
	MouseHurtState*	   hurtState	;
	MouseWhackedState* whackedState ;
	E_MOUSE_STATE e_mouseState = E_MOUSE_STATE::idleState;
private:
	void OnStateChange();
public:

	Mouse(Play::Point2D pos, E_MOUSE_COLOR COLOR = E_MOUSE_COLOR::DARK_GREY);
	Mouse(float x, float y, E_MOUSE_COLOR COLOR = E_MOUSE_COLOR::DARK_GREY);
	~Mouse();

	void SetMouseState(E_MOUSE_STATE e_state);

	void Update() override;

	void DrawBoundingBox() override;


};

