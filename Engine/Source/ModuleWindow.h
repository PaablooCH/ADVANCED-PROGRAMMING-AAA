#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init() override;

	// Called before quitting
	bool CleanUp() override;

	void SetFullScreen(bool& fullScreen);
	void SetBorderless(bool& borderless);
	void SetResizable(bool& resizable);
	void SetBrightness(float& brightness);
	void SetWidht(int& w);
	void SetHeight(int& h);

	float GetBrightness();

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;
	
	inline int& GetWidht() {
		return width;
	}
	inline int& GetMaxWidht() {
		return maxWidht;
	}
	inline int& GetHeight() {
		return height;
	}
	inline int& GetMaxHeight() {
		return maxHeight;
	}

private:
	int width, height, maxWidht, maxHeight;

};

#endif // __ModuleWindow_H__