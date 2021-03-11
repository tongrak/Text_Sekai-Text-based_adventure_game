#include"GUI.h"
#include"Program.h"

//Declare some object
GUI gui;
Data_loading load;
Player kami;

//Separeter

void SplitString(std::string in_text, std::string &key, std::string &wanted) {
	int holder = in_text.find_first_of(" ");
	key = in_text.substr(0, holder);
	wanted = in_text.substr(holder + 1);
}


/*
	Checking class, mainly for checking and process input
*/
Player::Player()
{
	Is_alive = true;

	if (load.LoadMaps()) std::cout << "Main::load Map loading and storing successfully" << std::endl;
	if (load.LoadEvent()) std::cout << "Main::load Event loading and storing successfully" << std::endl;
}
Player::~Player()
{

}

//Checking function
bool Player::CheckBasicCon() //Checking for basic condition for continue looping
{
	if (this->Is_alive) return true;
}

void Player::CheckInputText(std::string key, std::string wanted)
{
	if (key == "go")
	{
		if (wanted == " ") std::cout << "Player::CheckInputText no direction detected" << std::endl;
		else if (kami.CheckInputDir(wanted)) std::cout << "Player::CheckInputText got direction" <<std::endl;
		else std::cout << "Player::CheckInputText something went worng"<< std::endl;
	}
	if (key == "exit")
	{
		gui.ForceClose();
	}
}

bool Player::CheckInputDir(std::string wanted)
{
	std::string holder;
	bool check = false;
	unsigned int temp_int = 0;
	for (auto i : load.Direction) {
		if (wanted == i && load.GetNeighbors(temp_int, holder) != "NULL")
		{
			load.ChangeCurrentID(std::stoi(holder));
			check = true;
		}
		temp_int++;
	}
	return check;
}

//Setting function
void Player::SettingRoom()
{
	gui.UpdateText1(load.GetName());
	gui.UpdateText2(load.GetDes());
}




int main()
{
	std::string holder, t1="", t2="";
	load.ChangeCurrentID(1);

	while (gui.Running())
	{

		if(kami.CheckBasicCon())
		{
			//update
			kami.SettingRoom();
			if (gui.ChecknGetInputStr(holder)) 
			{
				SplitString(holder, t1, t2);
				kami.CheckInputText(t1, t2);

			}
			gui.Update();

			//render
			gui.Render();
		}

	}

	return 0;
}