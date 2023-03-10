#pragma once
#include "RectFill.h"
#include "Button.h"
#include <string.h>
#include <functional>
class InputBox:public RectFill
{
	typedef std::function<void()> FunctionType;
private:
	std::string inputText = "";
	const char* m_inputTitle = "";
	float inputValue = 0;
	float outputValue = 0;
	bool isTyping = false;
	FunctionType OnStateChangeHandler;
private:
	bool TextIsFloat(std::string s);
	void InputTextToValue();
public:
	InputBox(Play::Point2f pos, short sprite_height, short sprite_width, const char* spriteName, const char* title = "");
	~InputBox();

	void Render() override;

	bool OnClick() override;

	void OnStateChange();

	void GetInput();

	float GetOutput();

	void ClearInputText();
};

