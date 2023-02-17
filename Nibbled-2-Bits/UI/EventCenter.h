#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <string.h>
class Event {

	typedef std::function<void()> FunctionType;

private:
	std::vector<FunctionType> m_functions;//list of function?

public:

	Event(FunctionType function);

	void add(FunctionType function);

	void operator() () const;//overload brackets

};

class EventListener {
	static int id;
public:
	EventListener() { id++; }

	bool operator == (const EventListener& listener) const;

	virtual void onEvent(const Event* event);
};

namespace EventCenter
{
	void RegisterListener(const char* eventName, EventListener &listener);

	void UnregisterListener(const char* eventName, EventListener &listener);

	void UnregisterListener(const char* eventName);

	void PostEvent(const char* eventName, const Event& event);

	void DebugEvent();
}


