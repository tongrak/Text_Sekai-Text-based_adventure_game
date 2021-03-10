#include"GUI.h"
#include"Program.h"

int main()
{
	GUI gui;
	Data_loading Pro;
	Pro.ChangeCurrentID(1);
	if (!Pro.LoadMaps()) std::cout << "Main::load Map fail to load " << std::endl;
	if (!Pro.LoadEvent()) std::cout << "Main::load Event fail to load " << std::endl;

	while (gui.Running())
	{
		//update
		gui.UpdateText("Testing");
		gui.Update();
		
		//render
		gui.Render();
	}

	return 0;
}