#pragma once
#include "GameObject.h"
#include "../GameTool/Timer.h"
#include "MouseState.h"
#include "Component/Collider.h"
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

enum class E_MOUSE_DIR
{
	UP,
	LEFT,
	DOWN,
	RIGHT
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
	Play::Point2D prev_pos{ 0.0f,0.0f };
	const char* c_darkGrey = "_dark_grey_";
	const char* c_grey = "_grey_";
	const char* c_white = "_white_";
	const char* m_Color;
	float m_speed { 3.0f };
	float m_scale{ 1.0f };
	float m_height = 0.0f;
	float m_width = 0.0f;
	BoxCollider m_boxCollider;
	MouseState* m_state;
	MouseRunState*	   runState		;
	MouseDieState*	   dieState		;
	MouseIdleState*	   idleState	;
	MouseJumpState*	   jumpState	;
	MouseWalkState*	   walkState	;
	MouseHurtState*	   hurtState	;
	MouseWhackedState* whackedState ;
	E_MOUSE_DIR m_dir = E_MOUSE_DIR::UP;
	E_MOUSE_STATE e_mouseState = E_MOUSE_STATE::idleState;
private:
	void OnStateChange();
public:

	Mouse(Play::Point2D pos, E_MOUSE_COLOR COLOR = E_MOUSE_COLOR::DARK_GREY);
	Mouse(float x, float y, E_MOUSE_COLOR COLOR = E_MOUSE_COLOR::DARK_GREY);
	~Mouse();

	void SetMouseState(E_MOUSE_STATE e_state);

	void Update() override;

	void MouseControl();

	void SetPosition(Play::Point2D pos);
	
	BoxCollider& GetCollider();

	Play::Point2D GetPrevPos();
};

