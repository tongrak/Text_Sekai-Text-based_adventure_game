#include"GUI.h"
#include"Program.h"

#include<Windows.h>

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
	kami.CheckEvent();
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
	/*else if (key == "look")
	{
		Display text:
		-	
	}
	else if (key == "help")
	{
		Display text:
		- "You can input" on Text_name;
		- "'go' follow by a direction" on Text_line 1;
		- "'look' to look around yourself" on Text_line 2;
	*/
	else if (key == "exit")
	{
		gui.ForceClose();
	}
	/*
	else
	{
		Display text:
		-	"Sorry not quite get that" on Text_name;
		-	"input 'help' if you need one" on Text_line 1;
	}
	*/
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

void Player::CheckEvent()
{
	std::string hol_str;
	if (load.ChecknGetEventId(hol_str))
	{
		std::string opt1, opt2, con1, con2;
		load.ChangeEventID(std::stoi(hol_str));
		//load.CheckCheckpoint
		//Check for special event;
		//Check have event been active or not
		switch (load.GetEventType())
		{
		case 'S': //Cut-scene
			/*
				Check:
				-	Is Event been active or not;
				Display text from: 
				-	load.GetEventName on name_text_line 
				-	load.GetEventDes on text_line n so on
				Expect:
				-	player to press any key;
			*/
			std::cout << "Player::CheckEvent got S-type event." << std::endl;
			break;
		case 'B':
			/*
				Check:
				-	Is Event been active or not;
				Display text from:
				-	load.GetEventName on name_line
				-	load.GetEventDes on text_line
				-	load.GetEventOpt on last text_line
				Expect:
				-	player to input said Option, if valid active EventCondition.
			*/
			std::cout << "Player::CheckEvent got B-type event." << std::endl;
			break;
		/*case 'T':
			Check:
			-	Is Event been active or not;
			Display text from:
			-	load.GetEventName on name_line
			-	load.GetEventDes on text_line
			-	load.GetEventOpt on last text_line
			Expect:
			-	player to input said Option, if valid active EventCondition.
		*/
		default:
			std::cout << "Player::CheckEvent Check" << std::endl;
			break;
		}
		

		std::cout << "Player::CheckEvent got event id " << std::stoi(hol_str) << std::endl;
	}
	else 
	{
		std::cout << "Player::ChecEvent  no event detected" << std::endl;
	}
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
			//check
			if (gui.ChecknGetInputStr(holder))
			{
				SplitString(holder, t1, t2);
				kami.CheckInputText(t1, t2);
			}

			//update
			kami.SettingRoom();
			gui.Update();

			//render
			gui.Render();
		}

	}

	return 0;
}