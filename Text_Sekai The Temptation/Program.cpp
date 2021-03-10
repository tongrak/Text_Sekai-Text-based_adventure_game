#include"Program.h"

using namespace std;

/*
	Construtor and Distrutor
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
		if (hol_str == "EVENT_BEGIN") 
		{
			x = true;
			Room room_load;
			getline(file, hol_str);
			hol_int = stoi(hol_str);
			getline(file, room_load.name);
			getline(file, room_load.des);
			for (unsigned int i = 0; i < 4; i++)
			{
				getline(file, hol_str);
				int temp = hol_str.find_first_of(" ");
				room_load.Neighbor[i] = hol_str.substr(temp + 1);
			}
			getline(file, hol_str);
			int temp = hol_str.find_last_of(" ");
			room_load.eventID = hol_str.substr(temp + 1);
			roomStorage.insert(pair<int, Room>(hol_int, room_load));
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
	ifstream file("Resouces/Maps/Event.txt");
	while (getline(file, hol_str))
	{
		if (hol_str == "EVENT_BEGIN")
		{
			Event event_load;
			x = true;
			getline(file, hol_str);
			hol_int = stoi(hol_str);
			getline(file, event_load.event_name);
			getline(file, event_load.event_des);
			string temp1, temp2;
			getline(file, temp1);
			int temp_int = temp1.find_first_of(" ");
			temp2 = temp1.substr(temp_int + 1);
			event_load.event_typ = temp2[0];
			getline(file, event_load.event_opt);
			getline(file, event_load.event_condition);
			temp1, temp2;
			getline(file, temp1);
			temp_int = temp1.find_first_of(" ");
			temp2 = temp1.substr(temp_int + 1);
			(temp2 == "YES") ? event_load.event_check = true : event_load.event_check = false;
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
	return eventStorage[*Event_id].event_condition;
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

string Data_loading::GetEventId(string &holder)
{
	holder = roomStorage[*this->Current_id].eventID;
	return  roomStorage[*this->Current_id].eventID;
}
