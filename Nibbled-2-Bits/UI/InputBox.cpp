#include "pch.h"
#include "InputBox.h"
#include "../GameTool/DebugTool.h"
#include <sstream>
#include <string>

InputBox::InputBox(Play::Point2f pos, const char* spriteName, short sprite_height, short sprite_width,const char* title):RectFill(pos,spriteName,sprite_height,sprite_width)
{
	//btn_submit = Button({ pos.x + sprite_width / 2 + 20,pos.y }, "roundbtn", 50, 50, [] {},"Confirm");
	m_inputTitle = title;
}

InputBox::~InputBox()
{
}

void InputBox::Render(float scale)
{
	UIElement::Render(scale);
	DebugText(m_inputTitle, { m_pos.x - m_witdth / 2 - 50, m_pos.y });
	//btn_submit.DrawSprite(scale);
}

bool InputBox::OnClick()
{
	GetInput();
	if (UIElement::OnClick())
	{
		OnStateChange();
		DebugText("clicking");
		return true;
	}
	return false;
}

void InputBox::OnStateChange()
{
	isTyping = !isTyping;
}

bool InputBox::TextIsFloat(std::string s)
{
	std::istringstream iss(s);
	float temp;
	iss >> std::noskipws >> temp;
	return iss && iss.eof();     // Result converted to bool
}

void InputBox::InputTextToValue()
{
	if (TextIsFloat(inputText))
	{
		std::istringstream iss(inputText);
		float temp;
		iss >> std::noskipws >> temp;
		inputValue = temp;
		DebugValue(inputValue,"Valid: ");
	}
}

void InputBox::GetInput()
{
	if (isTyping)
	{
		if(Play::KeyPressed('0'))
			inputText += '0';
		if (Play::KeyPressed('1'))
			inputText += '1';
		if (Play::KeyPressed('2'))
			inputText += '2';
		if (Play::KeyPressed('3'))
			inputText += '3';
		if (Play::KeyPressed('4'))
			inputText += '4';
		if (Play::KeyPressed('5'))
			inputText += '5';
		if (Play::KeyPressed('6'))
			inputText += '6';
		if (Play::KeyPressed('7'))
			inputText += '7';
		if (Play::KeyPressed('8'))
			inputText += '8';
		if (Play::KeyPressed('9'))
			inputText += '9';
		if (Play::KeyPressed(VK_OEM_PERIOD))
			inputText += '.';
		if (Play::KeyPressed(VK_BACK))
		{
			if(!inputText.empty())
				inputText.pop_back();
		}
		DebugText(inputText,m_pos);
		//if (Play::KeyPressed(VK_RETURN))
		InputTextToValue();

		if(Play::KeyPressed(VK_RETURN))
		{
			outputValue = inputValue;
		}
	}
	else
	{
		ClearInputText();
	}
}

float InputBox::GetOutput()
{
	return outputValue;
}

void InputBox::ClearInputText()
{
	inputText = "";
	outputValue = 0;
}

