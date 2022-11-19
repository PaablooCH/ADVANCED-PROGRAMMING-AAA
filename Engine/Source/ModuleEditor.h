#pragma once
#include "Module.h"
#include "Application.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <vector>

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init() override;
	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	std::vector<const char*> logs;

private:
	void DrawLog(const char* title, bool& p_open);
	void DrawConfig(const char* title, bool& p_open);
	inline void ClearLog() {
		logs.clear();
	}

	std::vector<float> fpsLogs;
	std::vector<float> miliLogs;

	ImVec4 clear_color;
	int loops;
	int maxSizeFPS = 60;
	bool autoScroll;
	bool scrollToBottom;
};

