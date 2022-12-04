#pragma once
#include "Module.h"
#include "Application.h"
#include <vector>
#include<list>

class Panel;
class PanelAbout;
class PanelConfig;
class PanelConsole;
class PanelModel;

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
	bool FocusPanels();
	inline void ClearLog() {
		logs.clear();
	}

	inline const std::vector<float>& GetFps() {
		return fpsLogs;
	}
	inline const std::vector<float>& GetMili() {
		return miliLogs;
	}

	std::vector<const char*> logs;

private:
	bool DrawMainMenu();

	std::vector<float> fpsLogs;
	std::vector<float> miliLogs;
	std::list<Panel*> panels;

	PanelAbout* about = nullptr;
	PanelConfig* config = nullptr;
	PanelConsole* console = nullptr;
	PanelModel* model = nullptr;

	int loops;
	int maxSizeFPS = 60;
};

