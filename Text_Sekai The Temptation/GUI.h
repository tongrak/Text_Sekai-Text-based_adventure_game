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

class GUI {
public:
	//construtor and disstrutor
	GUI();
	virtual ~GUI();

	//some public function
	void Update();
	void Render();

	//Event
	void pollEvent();

	//Accessor
	const bool Running() const;


private:
	//declare some variable in need;
	sf::RenderWindow* window;
	sf::Event Eve;
	sf::VideoMode videomode;
	
	//text declaring
	sf::Text info;
	sf::Text in_arrow;
	sf::String sentence;
	


	//function
	void InitVar();
	void InitWindow();
	void InitText();

};

#endif // !DISPLAY_H
