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

#include<time.h>
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
	void Update_texture(int);
	void Update_titleSprite();
	void Update_BG(std::string);
	void UpdateText_title(std::string);
	void UpdateText_line1(std::string);
	void UpdateText_line2(std::string);
	void UpdateText_line3(std::string);
	void UpdateText_line4(std::string);
	void UpdateText_line5(std::string);
	void UpdateText_input();
	void StartTheGame();
	void WhiteText();
	void BlackText();
	//Rendering functions
	void Render();
	void RenderText_title(sf::RenderTarget& T);
	void RenderText_line1(sf::RenderTarget& H);
	void RenderText_line2(sf::RenderTarget& O);
	void RenderText_line3(sf::RenderTarget& O);
	void RenderText_line4(sf::RenderTarget& P);
	void RenderText_line5(sf::RenderTarget& D);
	//
	void RenderText_input(sf::RenderTarget& O);
	void RenderArrow(sf::RenderTarget& H);
	void RenderSprite(sf::RenderTarget& T);
	void RenderTitleSprite(sf::RenderTarget& A);
	void RenderStart(sf::RenderTarget& S);
	//Event
	void pollEvent();
	void InputText();
	void AnyInput();
	//void pollText();

	//Accessor
	const bool Running() const;
	bool ChecknGetInputStr(std::string &);
	bool CheckAnyPress();

	//Function
	void ForceClose();

	void InitSprite();
	void InitSpriteTitle();

private:
	//declare some variable in need;
	sf::RenderWindow* window;
	sf::Event Eve;
	sf::VideoMode videomode;
	
	//Resouces
	sf::Font font;

	//Picture Sprite
	sf::Sprite in_game;
	sf::Sprite in_title;
	sf::Sprite Start;

	//Texture
	sf::Texture texture;
	sf::Texture botton;

	//text declaring
	sf::Text Text_title;
	sf::Text Text_line1;
	sf::Text Text_line2;
	sf::Text Text_line3;
	sf::Text Text_line4;
	sf::Text Text_line5;
	sf::Text Text_input;
	sf::Text Arrow;

	//sf string for input
	sf::String input;

	//char array for getting user input
	char holder[33];

	//for store user input
	std::string* Input_holder;

	//Verification of a key
	bool anyKeyPressed;

	//function
	void InitVar();
	void InitWindow();
	void InitText();
	void InitTexture();


};

#endif // !DISPLAY_H
