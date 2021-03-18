#include"GUI.h"
#include"Program.h"

#include<Windows.h>

//Declare some object
//std::string holdmap;
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
	this->R_04 = true;
	this->R_43 = true;

	if (load.LoadMaps()) std::cout << "Main::load Map loading and storing successfully" << std::endl;
	if (load.LoadEvent()) std::cout << "Main::load Event loading and storing successfully" << std::endl;
}
Player::~Player()
{

}

void Player::AddItem(int item_key)
{
	this->Inventory.push_back(item_key);
}

bool Player::ChecknGetItemPosi(int wanted, int &return_posi)
{
	int posi;
	for (unsigned int i = 0; i < this->Inventory.size(); i++)
	{
		if (wanted == Inventory[i])
		{
			return_posi = i;
			return true;
		}
	}
	return false;
}

void Player::RemoveItem(int item_key)
{
	int hol_str;
	kami.ChecknGetItemPosi(item_key, hol_str);
	this->Inventory.erase(Inventory.begin()+hol_str);
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
		int hol_int = std::stoi(hol_str);
		load.ChangeEventID(hol_int);
		kami.CheckCheckPoint();
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
					gui.Update();
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
							else if (o1 != "NULL")
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
							if (o2 == "DEAD")
							{
								kami.DeclareDead();
							}
							else if (o2 != "NULL")
							{
								int temp = o2.find_last_of("_");
								hol_str = o2.substr(temp + 1);
								kami.AddItem(std::stoi(hol_str));
								std::cout << "Player::EventCheck got ItemID: " << std::stoi(hol_str) << std::endl;
							}
							check = true;
						}
					}
					gui.Render();
				} while (!check);
				break;
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
	bool check = false;
	int hol_int = load.GetCurrentID(), hol_item;
	std::string hol_str;
	/*Room with special event:
	roomID  Name		note
	!2	    sword		(repeat) Dead andf go back
	!4		Brige		Check:Wooden_board
	!7		Cabi_st		Check:Owner_permit
	!10		Gate		Check:coin(X)
	!23		ou_Citi		Check:Guild_direc
	!27		Pika		Check:Merch_pass, Berry, Poke-ball
	!39		Lava_pit	Check:Fishing rod
	!44		Dragon		3 chioces
	!43		Spider		Check:Fish fillet
	!16		Glove		Check:Holy herb
	!51		Sword V2	Check:Glove
	!53		Demon-load	Check:Sword
	!54		Princess	Check:Pillow
	!33		Merchent	Check:Pikachu
	!34		Cave Entry	Check:Torch
	17		Princess_ab	Long_cut
	*/
	if (hol_int == 2 && Is_alive)
	{
		gui.Update_texture(2);
		gui.UpdateText_title(load.GetName());
		kami.UpdatingTextInGen(load.GetDes());
		gui.UpdateText_line4("1)Take the sword  2)Walk away");
		do {
			gui.Update();
				if (gui.ChecknGetInputStr(hol_str))
				{
					if (hol_str == "1")
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("High voltage electrical power flow through your body, kill you instantly");
						gui.Render();
						kami.DeclareDead();
						kami.Hold();
						check = true;
					}
					if (hol_str == "2")
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("You turn around and walk back");
						gui.Render();
						kami.Hold();
						load.ChangeCurrentID(1);
						kami.SetGUIlook();
						check = true;
					}
				}
				gui.Render();
		} while (!check);
	}
	if (hol_int == 4 && Is_alive && R_04)
	{
		gui.Update_texture(4);
		gui.UpdateText_title(load.GetName());
		kami.UpdatingTextInGen(load.GetDes());
		gui.UpdateText_line4("1)go for it!  2)Fix the bridge  3)Go back");
		do {
			gui.Update();
			if (gui.ChecknGetInputStr(hol_str))
			{
				if (hol_str == "1")
				{
					kami.SetGUIclear();
					kami.UpdatingTextInGen("River deniel your attemp and kill you");
					gui.Render();
					kami.DeclareDead();
					kami.Hold();
					check = true;
				}
				else if (hol_str == "2")
				{
					if (kami.ChecknGetItemPosi(101, hol_item))//find Wooden board
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("you have fixed the bridge, now you can move through it now.");
						gui.Render();
						kami.Hold();
						this->R_04 = false;
						kami.RemoveItem(101);
						check = true;
					}
					else
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("you don't have anything to fix it.");
						gui.Render();
						kami.Hold();
					}
						
				}
				else if (hol_str == "3")
				{
					kami.SetGUIclear();
					kami.UpdatingTextInGen("you design to fall back, maybe some boards will help on bridge situation.");
					gui.Render();
					load.ChangeCurrentID(61);
					kami.Hold();
					check = true;
				}
			}
			gui.Render();
		} while (!check);
	}
	if (hol_int == 7 && Is_alive)
	{
		gui.Update_texture(7);
		if (kami.ChecknGetItemPosi(111, hol_item)) 
		{
			kami.SetGUIclear();
			kami.UpdatingTextInGen("Before you set your foot on the door frame, a arrow enter your chest. Ask for permition next time");
			gui.Render();
			kami.DeclareDead();
			kami.Hold();
		}
		
	}
	if (hol_int == 10 && Is_alive)
	{
		gui.Update_texture(10);
		gui.UpdateText_title(load.GetName());
		kami.UpdatingTextInGen(load.GetDes());
		gui.UpdateText_line4("1)turn back  2)go throght the gate");
		do {
			gui.Update();
			if (gui.ChecknGetInputStr(hol_str))
			{
				if (hol_str == "1")
				{
					kami.SetGUIclear();
					kami.UpdatingTextInGen("you turn back");
					kami.Hold();
					load.ChangeCurrentID(10);
					kami.SetGUIlook();
					check = true;
				}
				else if (hol_str == "2")
				{
					if (this->Coin > 120)
					{
						this->Coin -= 120;
						kami.SetGUIclear();
						kami.UpdatingTextInGen("you may enter said a guard");
						gui.Render();
						kami.Hold();
						load.ChangeCurrentID(13);
						kami.SetGUIlook();
						check = true;
					}
					else
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("Enter fee 120 copper coin, pay up or leave");
						gui.Render();
						kami.Hold();
					}

				}
			}
			gui.Render();
		} while (!check);
	}
	if (hol_int == 16 && Is_alive && R_16)
	{
		gui.Update_texture(16);
		gui.UpdateText_title(load.GetName());
		kami.UpdatingTextInGen(load.GetDes());
		if (kami.ChecknGetItemPosi(112, hol_item))
		{
			kami.UpdatingTextInGen("Just before you pick the gloves up, you starting to feel ill. luckly, you have a herb on you. you chew on the herb and walk away with gloves unharm");
			gui.Render();
			kami.AddItem(108);
			kami.RemoveItem(112);
			R_16 = false;
			kami.Hold();
		}
		else
		{
			kami.UpdatingTextInGen("Just before you pick the gloves up, you starting to feel ill. luckly, you have a herb on you. you chew on the herb and walk away with gloves unharm");
			gui.Render();
			kami.DeclareDead();
			kami.Hold();
		}
	}
	if (hol_int == 24 && Is_alive)
	{
		gui.Update_texture(7);
		if (kami.ChecknGetItemPosi(113, hol_item))
		{
			kami.SetGUIclear();
			kami.UpdatingTextInGen("walk, and walk you keep walking, but there aren't any cave in sight. Look like you lost. Next time get some guide from professional");
			gui.Render();
			kami.DeclareDead();
			gui.Render();
			kami.Hold();
		}
		
	}
	if (hol_int == 27 && Is_alive)
	{
		if (kami.ChecknGetItemPosi(104, hol_item))
		{

			gui.Update_texture(10);
			gui.UpdateText_title(load.GetName());
			kami.UpdatingTextInGen(load.GetDes());
			gui.UpdateText_line4("1)Chatch it!  2)I'm not ready  3)Use item...");
			do {
				gui.Update();
				if (gui.ChecknGetInputStr(hol_str))
				{
					if (hol_str == "1")
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("your attempt to chatch this yellow creature, result you kill by electric shock you off the ground and fly to middle of next week");
						gui.Render();
						kami.Hold();
						kami.DeclareDead();
						check = true;
					}
					else if (hol_str == "3")
					{
						if (kami.ChecknGetItemPosi(103, hol_item))
						{
							kami.SetGUIclear();
							kami.UpdatingTextInGen("you use throw a ball with color red and white, and manage to capture it");
							gui.Render();
							kami.AddItem(114);
							kami.Hold();
							check = true;
						}
						else
						{
							kami.SetGUIclear();
							kami.UpdatingTextInGen("the ceature throw the ball back at you and shock you with 100,000 voltage and send you fly off to the distance");
							gui.Render();
							kami.Hold();
							kami.DeclareDead();
							check = true;
						}
					}
					else if (hol_str == "2")
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("you need something to loolt ? the ceature first");
						gui.Render();
						kami.Hold();
						load.ChangeCurrentID(25);
						kami.SetGUIlook();
						check = true;
					}
				}
				gui.Render();
			} while (!check);
		}
	}
	if (hol_int == 33 && Is_alive && R_33)
	{
		kami.SetGUIclear();
		gui.UpdateText_title(load.GetName());
		
		do {
			gui.Update();
			if (gui.ChecknGetInputStr(hol_str))
			{
				if (R_33_1)
				{
					gui.UpdateText_title("The merchant");
					kami.UpdatingTextInGen("'Greeting traveler' said a merchant. 'It looks like you in need of tourchs. Here the deal, get me a yellow monster, the one with red cheeks'");
					gui.Render();
					kami.Hold();
					kami.SetGUIclear();
					kami.UpdatingTextInGen("capture it with this ball. And I shall give you these torchs");
					gui.Render();
					kami.Hold();
					R_33_1 = false;
					check = true;
				}
				if (kami.ChecknGetItemPosi(114, hol_item))
				{
					kami.SetGUIclear();
					kami.RemoveItem(114);
					gui.UpdateText_title("The happy merchant");
					kami.UpdatingTextInGen("'At last, you finally come with what I require' 'Here are the torchs and have a safe journey ahead'");
					kami.AddItem(102);
					this->R_33 = false;
					gui.Render();
					kami.Hold();
					check = true;
				}
			}
			gui.Render();
		} while (!check);

	}
	if (hol_int == 34 && Is_alive)
	{
		gui.Update_texture(34);
		gui.UpdateText_title(load.GetName());
		kami.UpdatingTextInGen(load.GetDes());
		gui.UpdateText_line4("1)Enter the cave 2)fall back for now");
		do {
			gui.Update();
			if (gui.ChecknGetInputStr(hol_str))
			{
				if (hol_str == "1")
				{
					if(kami.ChecknGetItemPosi(102, hol_item))
					{

						gui.UpdateText_title("The cave entry");
						kami.UpdatingTextInGen("you light the torch and march into darkness of the cave");
						gui.Render();
						kami.Hold();
						load.ChangeCurrentID(35);
						kami.SetGUIlook();
						check = true;
					}
					else
					{
						gui.UpdateText_title("The cave entry");
						kami.UpdatingTextInGen("The cave is soo pitch black, you'll need something to break this darkness");
						gui.Render();
						kami.Hold();
					}
				}
				if (hol_str == "2")
				{
					kami.SetGUIclear();
					kami.UpdatingTextInGen("You turn around and walk back");
					gui.Render();
					kami.Hold();
					load.ChangeCurrentID(32);
					kami.SetGUIlook();
					check = true;
				}
			}
			gui.Render();
		} while (!check);
	}
	if (hol_int == 39 && Is_alive)
	{
		gui.Update_texture(39);
		gui.UpdateText_title(load.GetName());
		kami.UpdatingTextInGen(load.GetDes());
				if (kami.ChecknGetItemPosi(106, hol_item))
				{
					kami.SetGUIclear();
					kami.UpdatingTextInGen("You got a catfish from the pit");
					gui.Render();
					kami.Hold();
					kami.AddItem(105);
					check = true;
				}
				else
				{
					kami.SetGUIclear();
					kami.UpdatingTextInGen("There are dozen of catfish in the lava pit and they look delicious");
					gui.Render();
					kami.Hold();
				}
	}
	if (hol_int == 44 && Is_alive)
	{
		gui.Update_texture(44);
		gui.UpdateText_title(load.GetName());
		kami.UpdatingTextInGen(load.GetDes());
		gui.UpdateText_line4("1)Show him what you got!!  2)Use something  3)Retreat!!!");
		do {
			gui.Update();
			if (gui.ChecknGetInputStr(hol_str))
			{
				if (hol_str == "1")
				{
					kami.SetGUIclear();
					kami.UpdatingTextInGen("It look like he too can see your ability and use water magic to cover you body. drown you in the spot!!");
					gui.Render();
					kami.DeclareDead();
					kami.Hold();
					check = true;
				}
				else if (hol_str == "2")
				{
					if (kami.ChecknGetItemPosi(107, hol_item))
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("you throw the pink spider at him. it look like spider give the dragon heart attack. anyone have their weakness I guess.");
						gui.Render();
						kami.Hold();
						kami.RemoveItem(107);

						check = true;
					}
					else
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("They aren't anything usefull in this situation. And the dragon design to kill you with a water magic.");
						gui.Render();
						kami.DeclareDead();
						kami.Hold();
					}

				}
				else if (hol_str == "3")
				{
					kami.SetGUIclear();
					kami.UpdatingTextInGen("you design to fall back, maybe some boards will help on bridge situation.");
					gui.Render();
					load.ChangeCurrentID(42);
					kami.SetGUIlook();
					kami.Hold();
					check = true;
				}
			}
			gui.Render();
		} while (!check);
	}
	if (hol_int == 43 && Is_alive && R_43) //spider
	{
		gui.Update_texture(44);
		gui.UpdateText_title(load.GetName());
		kami.UpdatingTextInGen(load.GetDes());
		gui.UpdateText_line4("1)Burn the net  2)Give her something  3)Leave the net");
		do {
			gui.Update();
			if (gui.ChecknGetInputStr(hol_str))
			{
				if (hol_str == "1")
				{
					kami.SetGUIclear();
					kami.UpdatingTextInGen("you make a decision to burn it all down, unfortunately before you can do so, a sharp pain come from your neck, look like you'd been bited. your vision gone black, now you are her dinner");
					gui.Render();
					kami.DeclareDead();
					kami.Hold();
					check = true;
				}
				else if (hol_str == "2")
				{
					if (kami.ChecknGetItemPosi(105, hol_item))
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("you begin a negotiation with the fish have caught. the talk go well, the spider agree to help you");
						gui.Render();
						kami.Hold();
						kami.RemoveItem(105);
						kami.AddItem(107);
						R_43 = false;
						check = true;
					}
					else
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("you don't have anything to use here. That spider look like it very hungry");
						gui.Render();
						kami.Hold();
					}

				}
				else if (hol_str == "3")
				{
					kami.SetGUIclear();
					kami.UpdatingTextInGen("you turn back");
					gui.Render();
					load.ChangeCurrentID(42);
					kami.SetGUIlook();
					kami.Hold();
					check = true;
				}
			}
			gui.Render();
		} while (!check);
	}
	if (hol_int == 51 && Is_alive && R_51)
	{
		gui.Update_texture(2);
		gui.UpdateText_title(load.GetName());
		kami.UpdatingTextInGen(load.GetDes());
		gui.UpdateText_line4("1)Take the sword  2)Just leave it alone");
		do {
			gui.Update();
			if (gui.ChecknGetInputStr(hol_str))
			{
				if (hol_str == "1")
				{
					if (kami.ChecknGetItemPosi(108, hol_item))
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("you use the glove to pull the sword. It come up with ease, and now you arm with something");
						gui.Render();
						kami.AddItem(109);
						this->R_51 = false;
						kami.Hold();
						check = true;
					}
					else
					{
						kami.SetGUIclear();
						kami.UpdatingTextInGen("High voltage electrical power flow through your body, kill you instantly. Ever Get That Feeling of Deja Vu?");
						gui.Render();
						kami.DeclareDead();
						kami.Hold();
						check = true;
					}
				}
				if (hol_str == "2")
				{
					kami.SetGUIclear();
					kami.UpdatingTextInGen("You turn around and walk back");
					gui.Render();
					kami.Hold();
					this->R_51 = false;
					load.ChangeCurrentID(50);
					kami.SetGUIlook();
					check = true;
				}
			}
			gui.Render();
		} while (!check);
	}
	if (hol_int == 53 && Is_alive && R_53)
	{
		gui.Update_texture(53);
		if (kami.ChecknGetItemPosi(109, hol_item))
		{
			kami.SetGUIclear();
			gui.UpdateText_title("The demon lord");
			kami.UpdatingTextInGen("Before you is the cause of all chaos, and all evil, Demon lord himself. without hesitation, you plant the sword on his chest, and end it all. only thing left is to rescue the pricess.");
			gui.Render();
			this->R_53 = false;
			kami.Hold();
			check = true;
		}
		else
		{
			kami.SetGUIclear();
			kami.UpdatingTextInGen("Before you is the cause of all chaos, and all evil, Demon lord himself. you can't feel nor control your owns limb.");
			gui.Render();
			kami.Hold();
			kami.UpdatingTextInGen("Just a blink of the eyes. Demon lord force your mouth open, then fill your mouth with chilies. The heat and the spice fill you head.");
			gui.Render();
			kami.Hold();
			kami.UpdatingTextInGen("Black, darkness fill your vision. any sensation stop. void fill the room, and this is how it all end");
			gui.Render();
			kami.Hold();
			gui.ForceClose();
		}
	}
	if (hol_int == 54 && Is_alive)
	{
		gui.Update_texture(54);
		if (kami.ChecknGetItemPosi(110, hol_item))
		{
			kami.SetGUIclear();
			gui.UpdateText_title("The Sleepless Princess");
			kami.UpdatingTextInGen("'A, He down already' said the pricess with a glowing marble in her hand...");
			gui.Render();
			kami.SetGUIclear();
			kami.UpdatingTextInGen("You wake up with completed project lay before you. What a long dream.");
			gui.Render();
			kami.Hold();
			gui.ForceClose();
		}
		else
		{
			kami.SetGUIclear();
			gui.UpdateText_title("The Princess");
			kami.UpdatingTextInGen("The beauty of all the land present in front of your. It time to return to the kingdom, the peaceful kingdom, and maybe it's time to settle down and life your life");
			gui.Render();
			kami.Hold();
			kami.SetGUIclear();
			kami.UpdatingTextInGen("In this fanstasy world");
			gui.Render();
			kami.Hold();
			gui.ForceClose();
		}
	}
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
		kami.CheckSpecialEvent();
		if(kami.CheckBasicCon())
		{
			
			kami.CheckEvent();
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
		gui.Update_texture(load.GetCurrentID());

			//render
		gui.Render();
		}

	return 0;
}