#include <stdlib.h>
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"
#include "Globals.h"

#include "SDL.h"
#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,  
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = NULL;

int main(int argc, char ** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			App = new Application();
			App->editor->logs.emplace_back("Application Creation --------------");
			state = MAIN_START;
			break;

		case MAIN_START:

			App->editor->logs.emplace_back("Application Init --------------");
			if (App->Init() == false)
			{
				App->editor->logs.emplace_back("Application Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				App->editor->logs.emplace_back("Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				App->editor->logs.emplace_back("Application Update exits with error -----");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			App->editor->logs.emplace_back("Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				App->editor->logs.emplace_back("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}

	}
	App->editor->logs.emplace_back("Bye :)\n");
	delete App;
	return main_return;
}
