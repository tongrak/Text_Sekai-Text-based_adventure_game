#pragma once
#ifndef ROOM_HPP
#define ROOM_HPP

#include<fstream>
#include<string>
#include<map>

struct Room
{
	std::string name;
	std::string des;
	std::string Neighbor[4];
	std::string eventID;

};

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

#endif 