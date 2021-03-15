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
	this->Is_alive = true;
	this->Coin =  0;


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
	else
	{
		kami.SetGUIclear();
		kami.setGUIdead();
	}
}

void Player::CheckInputText(std::string key, std::string wanted)
{
	if (key == "go")
	{
		if (wanted == " ") std::cout << "Player::CheckInputText no direction detected" << std::endl;
		else if (kami.CheckInputDir(wanted))
		{
			std::cout << "Player::CheckInputText got direction" << std::endl;
			kami.SetGUIclear();
			kami.SetGUIlook();
		}
		else std::cout << "Player::CheckInputText something went worng"<< std::endl;

	}
	else if (key == "look")
	{
		kami.SetGUIclear();
		kami.SetGUIlook();
	}
	else if (key == "help")
	{
		kami.SetGUIclear();
		kami.SetGUIhelp();
	}
	else if (key == "exit")
	{
		kami.SetGUIclear();
		gui.UpdateText_line4("go already?");
		bool veri = false;
		std::string temp_input;
		do {
			std::cout << "Do are you sure ?:";
			std::cin >> temp_input;
			if ( temp_input == "yes")
			{
				veri = true;
				gui.ForceClose();
			}
			else if (temp_input == "no")
			{
				veri = true;
				break;
			}
			else
			{
				std::cout << "It a yes or no question " <<std::endl;
			}
		} while (!veri);
	}
	else
	{
		kami.SetGUIclear();
		gui.UpdateText_line4("Sorry, not quite get that");
	}
}

bool Player::CheckInputDir(std::string wanted)
{
	std::string holder;
	bool check = false;
	unsigned int temp_int = 0;
	for (auto i : load.Direction) 
	{
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
		kami.CheckCheckPoint();
		//Check for special event;
		if (!load.GetEventAct())
		{
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
				gui.UpdateText_title(load.GetEventName());
				load.SentenceSpliter(load.GetEventDes(), load.SplitedLine);
				gui.UpdateText_line1(load.SplitedLine[0]);
				gui.UpdateText_line2(load.SplitedLine[1]);
				gui.UpdateText_line3(load.SplitedLine[2]);
				gui.UpdateText_line4(load.SplitedLine[3]);
				for (int i = 0; i < 4; i++)
				{
					load.SplitedLine[i] = " ";
				}
				system("pause");

				std::cout << "Player::CheckEvent got S-type event." << std::endl;
				break;
			case 'B': //Two option scene
			/*
					Check:
					-	Is Event been active or not;
					Display text from:
					-	load.GetEventName on name_line;
					-	load.GetEventDes on text_line;
					-	load.GetEventOpt on last text_line;
					Expect:
					-	player to input said Option, if valid active EventCondition;
			*/
				std::cout << "Player::CheckEvent got B-type event." << std::endl;
				break;
			/*
			case 'T': //Three option scene
				//----------//
					Check:
					-	Is Event been active or not;
					Display text from:
					-	load.GetEventName on name_line
					-	load.GetEventDes on text_line
					-	load.GetEventOpt on last text_line
					Expect:
					-	player to input said Option, if valid active EventCondition.
				//-----------//
			*/
			default:
				std::cout << "Player::CheckEvent Check" << std::endl;
				break;
			}
			load.ChangeEventToInAct();
			std::cout << "Player::CheckEvent got event id " << std::stoi(hol_str) << std::endl;
		}
	}
	else 
	{
		//std::cout << "Player::ChecEvent no event detected" << std::endl;
	}
}

void Player::CheckCheckPoint()
{
	if (load.GetLastCheck())
	{
		load.ChangeLastCheck();
		std::cout << "Player::CheckCheckPoint just change last checkpoint to " << load.GetLastCheck() << std::endl;
	}
}

void Player::DeclareDead()
{
	kami.Is_alive = false;
}

//Setting function
void Player::SetGUIlook()
{
	gui.UpdateText_title(load.GetName());
	load.SentenceSpliter(load.GetDes(), load.SplitedLine);
	gui.UpdateText_line1(load.SplitedLine[0]);
	gui.UpdateText_line2(load.SplitedLine[1]);
	gui.UpdateText_line3(load.SplitedLine[2]);
	gui.UpdateText_line4(load.SplitedLine[3]);
	for (int i = 0; i < 4; i++)
	{
		load.SplitedLine[i] = " ";
	}
}

void Player::SetGUIhelp()
{
	gui.UpdateText_title("You can type: ");
	gui.UpdateText_line1("'go' follow by direction");
	gui.UpdateText_line2("'look' around");
	gui.UpdateText_line3("'Exit'");
	gui.UpdateText_line4("");
	std::cout << "Player::SetGUIhelp have been set" << std::endl;
}

void Player::SetGUIstarting()
{
	//Usesing Intro-GUI
	
	kami.SetGUIlook();
	std::cout << "Player::SetGUIstarting have been activated " << std::endl;
}

void Player::SetGUIclear()
{
	gui.UpdateText_title(" ");
	gui.UpdateText_line1(" ");
	gui.UpdateText_line2(" ");
	gui.UpdateText_line3(" ");
	gui.UpdateText_line4(" ");
	std::cout << "Player::SetGUIclear have been activate" << std::endl;
}

void Player::setGUIdead()
{
	gui.UpdateText_line4("Do you want to go back?");
	std::cout << "Player::SetGUIdead have been activated" << std::endl;
}




int main()
{
	std::string holder, t1="", t2="";
	load.ChangeCurrentID(1);

	kami.SetGUIstarting();
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
			gui.Update();

			//render
			gui.Render();
		}

	}

	return 0;
}