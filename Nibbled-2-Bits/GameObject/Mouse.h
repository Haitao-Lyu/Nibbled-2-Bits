#pragma once
#include "GameObject.h"
#include "../GameTool/Timer.h"
#include "MouseState/MouseState.h"
#include "Component/BoxCollider.h"
#include "Component/CircleCollider.h"

#include "MouseState/MouseIdleState.h"
#include "MouseState/MouseHurtState.h"
#include "MouseState/MouseDieState.h"
#include "MouseState/MouseJumpState.h"
#include "MouseState/MouseRunState.h"
#include "MouseState/MouseWhackedState.h"
#include "MouseState/MouseWalkState.h"

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
	//TODO: Change restart function
	Play::Point2D prev_pos{ 0.0f,0.0f };
	const char* c_darkGrey = "_dark_grey_";
	const char* c_grey = "_grey_";
	const char* c_white = "_white_";
	const char* m_Color;
	float m_speed { 5.0f };

	MouseState* m_state;
	MouseRunState  m_runState;
	MouseDieState  m_dieState;
	MouseIdleState m_idleState;
	MouseJumpState m_jumpState;
	MouseWalkState m_walkState;
	MouseHurtState m_hurtState;
	MouseWhackedState m_whackedState;
	E_MOUSE_DIR m_dir = E_MOUSE_DIR::UP;
	E_MOUSE_STATE e_mouseState = E_MOUSE_STATE::idleState;
	bool isWhacked = false;
	bool isDead = false;
public:
	BoxCollider m_boxCollider;
	CircleCollider m_circleCollider;
private:
	void OnStateChange();
public:

	Mouse(Play::Point2D pos, E_MOUSE_COLOR COLOR = E_MOUSE_COLOR::DARK_GREY);
	Mouse(float x, float y, E_MOUSE_COLOR COLOR = E_MOUSE_COLOR::DARK_GREY);
	~Mouse() override;

	void SetMouseState(E_MOUSE_STATE e_state);

	void Update() override;

	void SetRotation(float dir);

	void OnRotationChanged();

	void DebugMouseControl();

	void SetPosition(Play::Point2D pos);

	void CheckBoxCollision();

	void CheckCircleCollision();

	BoxCollider& GetBoxCollider();

	CircleCollider& GetCollider();

	Play::Point2D GetPrevPos();
};

