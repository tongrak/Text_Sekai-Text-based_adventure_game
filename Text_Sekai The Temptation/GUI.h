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
	void UpdateText(std::string );

	//Rendering functions
	void Render();
	void RenderText(sf::RenderTarget &T);

	//Event
	void pollEvent();


	//Accessor
	const bool Running() const;


private:
	//declare some variable in need;
	sf::RenderWindow* window;
	sf::Event Eve;
	sf::VideoMode videomode;
	
	//Resouces
	sf::Font font;

	//text declaring
	sf::Text main_info;
	//sf::String sentence;
	


	//function
	void InitVar();
	void InitWindow();
	void InitText();

};

#endif // !DISPLAY_H
