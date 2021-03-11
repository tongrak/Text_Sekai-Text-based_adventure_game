#pragma once
#ifndef ROOM_HPP
#define ROOM_HPP

#include<fstream>
#include<string>
#include<map>

/*
	Here, lay game program.
*/

//Structure of Room
struct Room
{
	std::string name;
	std::string des;
	std::string Neighbor[4];
	std::string eventID;

};
//Structure of Event
struct Event
{
	std::string event_name;
	std::string event_des;
	char event_typ;
	std::string event_opt;
	bool event_act;
	std::string event_condition;
	bool event_check;
};
/*
	Data loading class, mainly doing loadind, storing, and returning string
	duties are...
	-	Loading and Storing(in map format, by key of map is that room id) Maps string;
	-	Loading and Storing(in map format, by key of map is that event id) Event string;
	-	Returning Name or Description of current stored room id;
	-	Returning Name or Description or Option or Condition or Checkpoint of current stored event id;
	-	Change current room or event id;
*/
class Data_loading {
public:
	//Loading function
	bool LoadMaps();
	bool LoadEvent();

	//Getting Var function 
	std::string GetName();
	std::string GetDes();
	char GetEventType();
	std::string GetEventName();
	std::string GetEventDes();
	std::string GetEventOpt();
	std::string GetEventCon();
	bool GetEventAct();
	bool GetEventCheck();
	int GetLastCheck();
	//Speacial getting var function
	std::string GetNeighbors(int dir, std::string &holder);
	std::string GetEventId(std::string &holder);

	//Changing var
	void ChangeCurrentID(int);
	void ChangeEventID(int);
	void ChangeEventToInAct();
	void ChangeLastCheck();

	//ruler
	std::string Direction[4] = { "north", "east", "west", "south" };

	//construtor and distrutor
	Data_loading();
	~Data_loading();

private:
	std::map<int, Room> roomStorage;
	std::map<int, Event> eventStorage;
	int* Current_id;
	int* Event_id;
	int* Last_check;
};

/*
	Checking class, mainly for checking and process input
*/
class Player
{
public:
	//Variable for checking
	bool Is_alive;

	//Checking Function
	bool CheckBasicCon();
	void CheckInputText(std::string , std::string);
	bool CheckInputDir(std::string);
	void CheckEvent();
	void CheckCheckPoint();

	//Design function
	void DeclareDead();

	//Setting function
	void SettingRoom();

	//Constructor and distructor
	Player();
	~Player();
};

#endif 