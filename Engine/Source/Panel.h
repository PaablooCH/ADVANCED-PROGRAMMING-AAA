#pragma once
class Panel
{
public:
	Panel(const char* title);
	virtual bool Draw() = 0;

	bool open = true;
protected:
	const char* title;
};

