#include "pch.h"
#include "EventCenter.h"
#include "../GameTool/DebugTool.h"


int EventListener::id = 0;

namespace EventCenter
{
	static std::map<const char*, std::vector<EventListener>> g_listeners_;

	void RegisterListener(const char* eventName, EventListener &listener)
	{
		DebugValue((int)g_listeners_.size());
		if (!g_listeners_[eventName].empty())
		{
			for (int i = 0; i < g_listeners_[eventName].size(); g_listeners_[eventName])
			{
				if (g_listeners_[eventName][i] == listener)//cmp id
				{
					return;
				}
			}
			g_listeners_[eventName].push_back(listener);
			return;
		}
		g_listeners_[eventName].push_back(listener);
	}

	void UnregisterListener(const char* eventName, EventListener &listener)
	{

	}

	void UnregisterListener(const char* eventName)
	{
		g_listeners_.erase(eventName);
	}

	void PostEvent(const char* eventName,const Event& event) 
	{
		if (g_listeners_.empty())
			return;
		DebugValue(static_cast<int>(g_listeners_[eventName].size()),"listener:",20);
		for (auto& listener : g_listeners_[eventName])
		{
			listener.onEvent(&event);
		}
	}

	void DebugEvent()
	{

	}
}


Event::Event(FunctionType function)
{
	add(function);
}

void Event::add(FunctionType function)
{
	m_functions.push_back(function);
}

void Event::operator()() const
{
	for (auto& f : m_functions)
	{
		f();
	}
}

bool EventListener::operator==(const EventListener& listener) const
{
	if (id == listener.id)
		return true;
	return false;
}

void EventListener::onEvent(const Event* event)
{
	(*event)();
}

