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
	void UpdateText1(std::string);
	void UpdateText2(std::string);
	void UpdateText3(std::string);
	void UpdateText4(std::string);
	void UpdateText5(std::string);

	//Rendering functions
	void Render();
	void RenderText1(sf::RenderTarget &T);
	void RenderText2(sf::RenderTarget &H);
	void RenderText3(sf::RenderTarget &O);
	void RenderText4(sf::RenderTarget &O);
	void RenderText5(sf::RenderTarget &P);

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
	sf::Text main_line1;
	sf::Text main_line2;
	sf::Text main_line3;
	sf::Text main_line4;
	sf::Text main_line5;
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
