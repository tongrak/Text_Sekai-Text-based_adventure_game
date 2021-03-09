#include"GUI.h"

int main()
{
	GUI gui;

	while (gui.Running())
	{
		//update
		gui.Update();
		
		//render
		gui.Render();
	}

	return 0;
}