#pragma once
class Panel
{
public:
	Panel(const char* title);
	virtual bool Draw() = 0;

	inline bool& GetOpen() {
		return open;
	}
	inline void SetOpen(const bool& op) {
		open = op;
	}
	inline const bool GetFocus() {
		return focus;
	}

protected:
	const char* title;
	bool open = true;
	bool focus = false;
};

