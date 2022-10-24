#pragma once
class String
{
public:
	String(const char* str);
	String(const String&& a);
	int lenght();
	void clear();
	String& operator= (const String& a);
	String& operator== (String&& a);
	String& operator+ (String a);
	void Write();

private:
	const char* string;
};

