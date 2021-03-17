#include"Program.h"

using namespace std;

void Data_loading::SentenceSpliter(std::string input_str, std::string input_arr[])
{
	int start = 0, end = start + 60;
	bool stop = true;
	for (int i = 0; i < 4; i++) // new line
	{
		if (end < input_str.size() && stop == true)
		{
			if (input_str[end] != ' ') end = input_str.find_first_of(" ", end);
			input_arr[i] = input_str.substr(start, end - start);
			input_str.erase(start, end);
		}
		else
		{
			if (input_str.size() - start < 60 && stop == true)
			{
				input_arr[i] = input_str.substr(start, input_str.size() - start);
				stop = false;
				break;
			}
			else input_arr[i] = " ";
			break;
		}
	}
}

/*
	Construtor and Distrutor for Data_loading class, and it member shall begen here
*/
Data_loading::Data_loading()
{
	this->Current_id = new int;
	this->Event_id = new int;
	this->Last_check = new int;

	*this->Current_id = 0;
	*this->Event_id = 0;
	*this->Last_check = 0;
}

Data_loading::~Data_loading() 
{
	delete Current_id;
	delete Event_id;
	delete Last_check;
}

/*
	Maps Loading Function
*/
bool Data_loading::LoadMaps()
{
	string hol_str;
	int hol_int;
	bool x = false;
	ifstream file("Resouces/Maps/Maps.txt");
	while(getline(file, hol_str))
	{
		if (hol_str == "ROOM_BEGIN") 
		{
			x = true;
			Room room_load;
			//load room id
			getline(file, hol_str);
			hol_int = stoi(hol_str);
			std::cout << "Data_loading::LoadMaps room id:" << hol_int << std::endl;
			//load room name
			getline(file, room_load.name);
			std::cout << "Data_loading::LoadMaps room name: " << room_load.name << std::endl;
			//load room des
			getline(file, room_load.des);
			std::cout << "Data_loading::LoadMaps room des: " << room_load.des << std::endl;
			//load room neighboring room id
			for (unsigned int i = 0; i < 4; i++)
			{
				getline(file, hol_str);
				int temp = hol_str.find_first_of(" ");
				std::cout << "Data_loading::LoadMaps neighbor id: " << hol_str.substr(temp + 1) << std::endl;
				room_load.Neighbor[i] = hol_str.substr(temp + 1);
			}
			//load room event id
			getline(file, hol_str);
			int temp = hol_str.find_last_of(" ");
			room_load.eventID = hol_str.substr(temp + 1);
			std::cout << "Data_loading::LoadMaps event id: " << hol_str.substr(temp + 1) << std::endl;
			//Storing
			roomStorage.insert(pair<int, Room>(hol_int, room_load));
			std::cout << std::endl;
		}
	}
	file.close();
	return x;
}

bool Data_loading::LoadEvent()
{
	string hol_str;
	int hol_int;
	bool x = false;
	ifstream file("Resouces/Maps/Events.txt");
	while (getline(file, hol_str))
	{
		if (hol_str == "EVENT_BEGIN")
		{
			Event event_load;
			x = true;
			//load event id
			getline(file, hol_str);
			hol_int = stoi(hol_str);
			//load event name
			getline(file, event_load.event_name);
			getline(file, event_load.event_des);
			string temp1, temp2;
			//spilt
			getline(file, temp1);
			int temp_int = temp1.find_first_of(" ");
			temp2 = temp1.substr(temp_int + 1);
			//load event type
			event_load.event_typ = temp2[0];
			//load event option
			getline(file, event_load.event_opt);
			//load event outcome
			getline(file, event_load.event_outCome);
			getline(file, temp1);
			//load post event 01
			getline(file, event_load.event_PosOutCome01);
			//load post event 02
			getline(file, event_load.event_PosOutCome02);
			//Spilt
			temp_int = temp1.find_first_of(" ");
			temp2 = temp1.substr(temp_int + 1);
			//check for checkpoint
			(temp2 == "YES") ? event_load.event_check = true : event_load.event_check = false;
			event_load.event_act = false;
			eventStorage.insert(pair<int, Event>(hol_int, event_load));
		}
	}
	file.close();
	return x;
}


/*
	Change function
*/
void Data_loading::ChangeCurrentID(int id)
{
	*this->Current_id = id;
}

void Data_loading::ChangeEventID(int id)
{
	*this->Event_id = id;
}

void Data_loading::ChangeEventToInAct()
{
	this->eventStorage[*Event_id].event_act = true;
}

void Data_loading::ChangeLastCheck()
{
	*this->Last_check = *this->Current_id;
}

/*
	'Getting' function
*/
int Data_loading::GetCurrentID()
{
	return *this->Current_id;
}

string Data_loading::GetName()
{
	return roomStorage[*Current_id].name;
}

string Data_loading::GetDes()
{
	return roomStorage[*Current_id].des;
}

char Data_loading::GetEventType()
{
	return eventStorage[*Event_id].event_typ;
}

string Data_loading::GetEventName()
{
	return eventStorage[*Event_id].event_name;
}

string Data_loading::GetEventDes()
{
	return eventStorage[*Event_id].event_des;
}

string Data_loading::GetEventOpt()
{
	return eventStorage[*Event_id].event_opt;
}

string Data_loading::GetEventCon()
{
	return eventStorage[*Event_id].event_outCome;
}

bool Data_loading::GetEventAct()
{
	return eventStorage[*Event_id].event_act;
}

bool Data_loading::GetEventCheck()
{
	return eventStorage[*Event_id].event_check;
}

int Data_loading::GetLastCheck()
{
	return *this->Last_check;
}
//Special Get var function
string Data_loading::GetNeighbors(int dir, string &holder)
{
	holder = roomStorage[*this->Current_id].Neighbor[dir];
	return roomStorage[*this->Current_id].Neighbor[dir];
}

bool Data_loading::ChecknGetEventId(string &holder)
{
	//std::cout << "Data_loading::ChecknGetEventId :" << roomStorage[*this->Current_id].eventID << std::endl;
	if (roomStorage[*this->Current_id].eventID != "NULL")
	{
		holder = roomStorage[*this->Current_id].eventID;
		return true;
	}
	else
	{
		holder = "NULL";
		return false;
	}
	
	
}

