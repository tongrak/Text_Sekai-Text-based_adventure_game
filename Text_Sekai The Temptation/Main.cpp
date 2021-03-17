#include"GUI.h"
#include"Program.h"

#include<Windows.h>

//Declare some object
std::string holdmap;
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

void Player::AddItem(int item_key)
{
	this->Inventory.insert(item_key);
}

void Player::RemoveItem(int item_key)
{
	this->Inventory.erase(Inventory.find(item_key));
}

//Checking function
bool Player::CheckBasicCon() //Checking for basic condition for continue looping
{
	if (this->Is_alive) return true;
	else
	{
		kami.SetGUIclear();
		kami.setGUIdead();
		kami.Hold();
		return false;
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
			kami.UpdatingTextInGen(load.GetDes());
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
			kami.CheckSpecialEvent();
			::holdmap = holder;
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
		int hol_int = std::stoi(hol_str);
		load.ChangeEventID(hol_int);
		kami.CheckCheckPoint();
		kami.CheckSpecialEvent();
		if (!load.GetEventAct())
		{
			std::string hol_str, s1, s2 , o1, o2;
			int temp_int;
			bool check = false;
			switch (load.GetEventType())
			{
			case 'S': //Cut-scene
				std::cout << "Player::CheckEvent got S-type event." << std::endl;
				gui.UpdateText_title(load.GetEventName());
				kami.UpdatingTextInGen(load.GetEventDes());
				gui.Render();
				do
				{
					std::cout << "Player::CheckEvent I'm in S-loop" << std::endl;
					gui.pollEvent();
					if (gui.CheckAnyPress())
						check = true;
				} while (!check);
				kami.SetGUIlook();
				break;
			case 'B': //Two option scene
				std::cout << "Player::CheckEvent got B-type event." << std::endl;
				gui.UpdateText_title(load.GetEventName());
				kami.UpdatingTextInGen(load.GetEventDes());
				hol_str = load.GetEventOpt();
				std::cout << "Player::CheckEvent got option: " << hol_str<< std::endl;
				SplitString(hol_str, s1, s2);
				gui.UpdateText_line4("Please enter " + s1 + " " + s2);
				SplitString(load.GetEventOutC(), o1, o2);
				do
				{
					gui.pollEvent();
					if (gui.ChecknGetInputStr(hol_str))
					{
						if (hol_str == "1")
						{
							kami.SetGUIclear();
							kami.UpdatingTextInGen(load.GetEventPos1());
							if(o1 == "DEAD")
							{
								kami.DeclareDead();
							}
							check = true;
						}
						else if (hol_str == "2")
						{
							kami.SetGUIclear();
							kami.UpdatingTextInGen(load.GetEventPos2());
							if (o2 == "DEAD")
							{
								kami.DeclareDead();
							}
							check = true;
						}
						else
						{
							gui.UpdateText_line4("Please type in: 1 or 2");
						}
					}
					gui.Update();
					gui.Render();
				} while (!check);
				kami.Hold();
				break;
			case 'T': //Three option scene
				std::cout << "Player::CheckEvent got T-type event." << std::endl;
				gui.UpdateText_title(load.GetEventName());
				kami.UpdatingTextInGen(load.GetEventDes());
				hol_str = load.GetEventOpt();
				std::cout << "Player::CheckEvent got option: " << hol_str << std::endl;
				SplitString(hol_str, s1, s2);
				gui.UpdateText_line4("Please enter " + s1 + " " + s2);
				SplitString(load.GetEventOutC(), o1, o2);
				do
				{
					gui.pollEvent();
					if (gui.ChecknGetInputStr(hol_str))
					{
						if (hol_str == "1")
						{
							kami.SetGUIclear();
							kami.UpdatingTextInGen(load.GetEventPos1());
							if (o1 != "NULL")
							{
								int temp = o1.find_last_of(":");
								hol_str = o1.substr(temp + 1);
								kami.AddItem(std::stoi(hol_str));
								std::cout << "Player::EventCheck got ItemID: " << std::stoi(hol_str) << std::endl;
							}
							check = true;
						}
						else if (hol_str == "2")
						{
							kami.SetGUIclear();
							kami.UpdatingTextInGen(load.GetEventPos2());
							if (o2 != "NULL")
							{
								int temp = o2.find_last_of("_");
								hol_str = o2.substr(temp + 1);
								kami.AddItem(std::stoi(hol_str));
								std::cout << "Player::EventCheck got ItemID: " << std::stoi(hol_str) << std::endl;
							}
							check = true;
						}
						else
						{
							gui.UpdateText_line4("Please type in: 1 or 2");
						}
					}
					gui.Update();
					gui.Render();
				} while (!check);
				kami.Hold();
			default:
				std::cout << "Player::CheckEvent Check" << std::endl;
				break;
			}
			load.ChangeEventToInAct();
			std::cout << "Player::CheckEvent got event id " << hol_int << std::endl;
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

void Player::CheckSpecialEvent()
{
	/*Room with special event:
	roomID  Name		note
	2	    sword		(repeat) Dead andf go back
	4		Brige		Check:Wooden_board
	7		Cabi_st		Check:Owner_permit
	10		Gate		Check:coin(X)
	23		ou_Citi		Check:Guild_direc
	27		Pika		Check:Merch_pass, Berry, Poke-ball
	39		Lava_pit	Check: Fishing rod
	44		Dragon		3 chioces
	45		Spider		Check: Fish fillet
	51		Sword V2	Check:Glove
	53		Demon-load	Check:Sword
	54		Princess	Check:Pillow, 3 choices
	*/
}

void Player::DeclareDead()
{
	kami.Is_alive = false;
}

void Player::UpdatingTextInGen(std::string in_text)
{
	gui.UpdateText_title(load.GetName());
	load.SentenceSpliter(in_text, load.SplitedLine);
	gui.UpdateText_line1(load.SplitedLine[0]);
	gui.UpdateText_line2(load.SplitedLine[1]);
	gui.UpdateText_line3(load.SplitedLine[2]);
	gui.UpdateText_line4(load.SplitedLine[3]);
	for (int i = 0; i < 4; i++)
	{
		load.SplitedLine[i] = " ";
	}
}

//Setting function
void Player::SetGUIlook()
{
	kami.UpdatingTextInGen(load.GetDes());
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
	gui.UpdateText_title("You are History.");
	gui.UpdateText_line4("Do you want to go back?");
	std::cout << "Player::SetGUIdead have been activated" << std::endl;
}

void Player::Hold()
{
	bool check = false;
	do
	{
		gui.pollEvent();
		if (gui.CheckAnyPress())
			check = true;
	} while (!check);
}






int main()
{
	std::string holder, t1="", t2="";
	load.ChangeCurrentID(0);

	kami.SetGUIstarting();
	while (gui.Running())
	{
		kami.CheckEvent();
		kami.CheckSpecialEvent();
		if(kami.CheckBasicCon())
		{
			
			kami.SetGUIlook();
			//check
			if (gui.ChecknGetInputStr(holder))
			{
				SplitString(holder, t1, t2);
				kami.CheckInputText(t1, t2);
			}
		}
		else
		{
			if (gui.ChecknGetInputStr(holder))
			{
				if (holder == "yes")
				{
					kami.Is_alive = true;
					load.ChangeCurrentID(load.GetLastCheck());
				}
				else if (holder == "no")
				{
					gui.ForceClose();
				}
			}
		}
		//update
		gui.Update();

		//gui.Update_BG(::holdmap);
		gui.Update_texture(::holdmap);

			//render
		gui.Render();
		}

	return 0;
}