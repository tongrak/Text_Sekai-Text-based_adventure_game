#pragma once
#ifndef GUI_H
#define GUI_H

/*
	Here, lay the game GUI.
*/
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>

#include<iostream>
#include<sstream>
#include<string>

class GUI {
public:
	//construtor and disstrutor
	GUI();
	virtual ~GUI();

	//Updating functions
	void Update();
	void UpdateText_title(std::string);
	void UpdateText_line1(std::string);
	void UpdateText_line2(std::string);
	void UpdateText_line3(std::string);
	void UpdateText_line4(std::string);
	void UpdateText_input();
	//update arrow
	void UpdateArrow(std::string);

	//Rendering functions
	void Render();
	void RenderText_title(sf::RenderTarget&T);
	void RenderText_line1(sf::RenderTarget&H);
	void RenderText_line2(sf::RenderTarget&O);
	void RenderText_line3(sf::RenderTarget&O);
	void RenderText_line4(sf::RenderTarget&P);
	//
	void RenderText_input(sf::RenderTarget& O);
	void RenderArrow(sf::RenderTarget& H);

	//Event
	void pollEvent();
	void InputText();

	//Accessor
	const bool Running() const;
	bool ChecknGetInputStr(std::string &);

	//Function
	void ForceClose();


private:
	//declare some variable in need;
	sf::RenderWindow* window;
	sf::Event Eve;
	sf::VideoMode videomode;
	
	//Resouces
	sf::Font font;

	//text declaring
	sf::Text Text_title;
	sf::Text Text_line1;
	sf::Text Text_line2;
	sf::Text Text_line3;
	sf::Text Text_line4;
	sf::Text Text_input;

	//string 

	//sf string for input
	sf::String input;

	//char array for getting user input
	char holder[33];

	//for store user input
	std::string* Input_holder;

	//function
	void InitVar();
	void InitWindow();
	void InitText();

};

#endif // !DISPLAY_H
