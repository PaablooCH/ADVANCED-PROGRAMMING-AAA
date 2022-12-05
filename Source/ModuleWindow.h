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

	void SetFullScreen(bool& full);
	inline bool& GetFullScreen() {
		return fullScreen;
	};
	void SetBorderless(bool& bordless);
	inline bool& GetBorderless() {
		return borderless;
	};
	void SetResizable(bool& resi);
	inline bool& GetResizable() {
		return resizable;
	}
	inline void SetFullDsktp(const bool& fDsktp) {
		fullDsktp = fDsktp;
	}
	inline bool& GetFullDsktp() {
		return fullDsktp;
	}
	void SetBrightness(float& brightness);
	void SetWidht(int& w);
	void SetHeight(int& h);
	void SetPosition(const int& x, const int& y);

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

	bool fullScreen, borderless, resizable, fullDsktp;

};

#endif // __ModuleWindow_H__