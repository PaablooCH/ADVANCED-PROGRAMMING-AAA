#pragma once
class String
{
public:
	String(const char* str);
	String(const String&& a);
	inline int Lenght() {
		return lenght;
	};
	void clear();
	String& operator= (const String& a);
	bool operator== (const char* a);
	String operator+ (const String& a);
	void Write();

private:
	const char* string;
	int lenght;
};

