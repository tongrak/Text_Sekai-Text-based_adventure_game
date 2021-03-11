/*
	This is where Display.h is innitialize
*/
#include"GUI.h"


/*
	constructors and distrutor zone
*/
GUI::GUI()
{
	this->InitVar();
	this->InitWindow();
	this->InitText();
}

GUI::~GUI()
{
	delete this->window;
	std::cout << "GUI ending successfully" << std::endl;
}

/*
	Accessor
*/

const bool GUI::Running() const
{
	return this->window->isOpen();
}

/*
	Updating Function
*/
void GUI::Update()
{
	this->pollEvent();
	//this->UpdateText();
}
//Updating text
void GUI::UpdateText1(std::string s1)
{
	std::stringstream ss1;
	ss1 << s1;
	this->main_line1.setString(ss1.str());
}
void GUI::UpdateText2(std::string s2)
{
	std::stringstream ss2;
	ss2 << s2;
	this->main_line2.setString(ss2.str());
}
void GUI::UpdateText3(std::string s3) 
{
	std::stringstream ss3;
	ss3 << s3;
	this->main_line3.setString(ss3.str());
}
//void GUI::UpdateText4(std::string s4)
//{
//
//}
//void GUI::UpdateText3(std::string s5) 
//{
//
//}


/*
	Rendering Function
*/
void GUI::Render()
{
	this->window->clear(sf::Color::White);

	this->UpdateText3(this->input);
	this->RenderText1(*this->window);
	this->RenderText2(*this->window);
	this->RenderText3(*this->window);
	this->RenderText4(*this->window);
	this->RenderText5(*this->window);

	this->window->display();
}
//Rendering Text line at said number; 
void GUI::RenderText1(sf::RenderTarget& T)
{
	T.draw(this->main_line1);
}
void GUI::RenderText2(sf::RenderTarget& H)
{
	H.draw(this->main_line2);
}
void GUI::RenderText3(sf::RenderTarget& O)
{
	O.draw(this->main_line3);
}
void GUI::RenderText4(sf::RenderTarget& O)
{
	O.draw(this->main_line4);
}
void GUI::RenderText5(sf::RenderTarget& P)
{
	P.draw(this->main_line5);
}

/*
	Poll Event
*/
void GUI::pollEvent()
{
	//Event polling.
	while (this->window->pollEvent(this->Eve))
	{
		//Checking event happening.
		switch (this->Eve.type)
		{
		//For close buttom.
		case sf::Event::Closed:
			std::cout << "Event::Eve You just pressed X" << std::endl;
			this->window->close();
			break;
		//For when press Escape key.
		case sf::Event::KeyPressed:
			if (this->Eve.key.code == sf::Keyboard::Escape)
			{
				std::cout << "Event::Eve You just pressed Escape buttom" << std::endl;
				this->window->close();
			}
			break;
		//Showing current resolutiom if changed.
		case sf::Event::Resized:
			printf("Current resolution:%i,%i\n", Eve.size.width, Eve.size.height);
			break;
		//For entering text.
		case sf::Event::TextEntered:
			this->InputText();

		default:
			break;
		}
	}
}

void GUI::InputText()
{
		if (this->Eve.text.unicode >= 32 && Eve.text.unicode <= 126 && input.getSize() < 20) // รับอินพุทต์แค่ 32 - 126 ในตารางยูนิโค้ดและจำกัดมันไว้แค่ 20 ตัวอักษร
		{
			
			input += (char)Eve.text.unicode; // ใส่ตัวอักษร char ทีละตัวลงไป
		}
		else if (Eve.text.unicode == 8 /*Delete key*/ && input.getSize() > 0) // ลบตัวอักษร
		{
			input.erase(input.getSize() - 1, input.getSize()); // ลบตามขนาดลงไปทีละตัว
		}
		else if (Eve.text.unicode == 13/*Enter key*/ && input.getSize()) // กด ENTER 
		{
			for (unsigned int i = 0; i < input.getSize(); i++)
			{
				this->holder[i] = tolower(this->input[i]);
			}
			std::cout << "GUI::Input I got :" << this->holder << std::endl;
			
			input.clear();
		}
}


/*
	Returning function
*/

bool GUI::ChecknGetInputStr(std::string &s1)
{
	if (*this->holder != 0)
	{
		s1 = holder;
		memset(holder, 0, strlen(holder));
		return true;
	}
	else return false;
}


/*
	Initialize stuff
*/

void GUI::InitVar()
{
	this->window = nullptr;
}

void GUI::InitWindow()
{
	this->videomode.height = 1048;
	this->videomode.width = 1048;
	this->window = new sf::RenderWindow(this->videomode, "Text Adventure", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	this->window->setFramerateLimit(30);
}

void GUI::InitText()
{	
	//loading font
	if(this->font.loadFromFile("Resouces/Font/Simple_text.ttf"))
	{
		std::cout << "GUI::font loaded successfully"<<std::endl;
	}

	//Setting Inout text


	//Setting main_ text	
	this->main_line1.setFont(this->font);
	this->main_line1.setCharacterSize(23);
	this->main_line1.setFillColor(sf::Color::Black);
	this->main_line1.setPosition(50, 660);

	this->main_line2.setFont(this->font);
	this->main_line2.setCharacterSize(23);
	this->main_line2.setFillColor(sf::Color::Black);
	this->main_line2.setPosition(50, 700);

	this->main_line3.setFont(this->font);
	this->main_line3.setCharacterSize(23);
	this->main_line3.setFillColor(sf::Color::Black);
	this->main_line3.setPosition(50, 740);

	this->main_line4.setFont(this->font);
	this->main_line4.setCharacterSize(23);
	this->main_line4.setFillColor(sf::Color::Black);
	this->main_line4.setPosition(50, 560);

	this->main_line5.setFont(this->font);
	this->main_line5.setCharacterSize(23);
	this->main_line5.setFillColor(sf::Color::Black);
	this->main_line5.setPosition(50, 620);

}

void GUI::ForceClose()
{
	std::cout << std::endl <<"GUI::ForceClose you just force close a game";
	this->window->close();
}
