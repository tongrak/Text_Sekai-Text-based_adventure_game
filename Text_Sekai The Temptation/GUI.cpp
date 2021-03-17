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
	this->InitSprite();
	this->InitTexture();
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
	this->UpdateText_input();
	/*if (time_t % 3 == 0) {
		this->Arrow.setFillColor(sf::Color::White);
	}
	else this->Arrow.setFillColor(sf::Color::Black);*/
	this->anyKeyPressed = false;
}
//Updating text
void GUI::UpdateText_title(std::string s1)
{
	std::stringstream ss1;
	ss1 << s1;
	this->Text_title.setString(ss1.str());
}
void GUI::UpdateText_line1(std::string s2)
{
	std::stringstream ss;
	ss << s2;
	this->Text_line1.setString(ss.str());
}
void GUI::UpdateText_line2(std::string s3) 
{
	std::stringstream ss3;
	ss3 << s3;
	this->Text_line2.setString(ss3.str());
}
void GUI::UpdateText_line3(std::string s4)
{
	std::stringstream ss4;
	ss4 << s4;
	this->Text_line3.setString(ss4.str());
}
void GUI::UpdateText_line4(std::string s5) 
{
	std::stringstream ss5;
	ss5 << s5;
	this->Text_line4.setString(ss5.str());
}

void GUI::UpdateText_line5(std::string s6) 
{
	std::stringstream ss6;
	ss6 << s6;
	this->Text_line4.setString(ss6.str());
}

void GUI::UpdateText_input()
{
	this->Text_input.setString(this->input);
}



/*
	Rendering Function
*/
void GUI::Render()
{
	this->window->clear(sf::Color::White);

	this->RenderSprite(*this->window);
	this->RenderText_title(*this->window);
	this->RenderText_line1(*this->window);
	this->RenderText_line2(*this->window);
	this->RenderText_line3(*this->window);
	this->RenderText_line4(*this->window);
	this->RenderText_line5(*this->window);

	this->RenderText_input(*this->window);
	this->RenderArrow(*this->window);

	this->window->display();
}
//Rendering Text line at said number; 
void GUI::RenderText_title(sf::RenderTarget& T)
{
	T.draw(this->Text_title);
}
void GUI::RenderText_line1(sf::RenderTarget& H)
{
	H.draw(this->Text_line1);
}
void GUI::RenderText_line2(sf::RenderTarget& O)
{
	O.draw(this->Text_line2);
}
void GUI::RenderText_line3(sf::RenderTarget& O)
{
	O.draw(this->Text_line3);
}
void GUI::RenderText_line4(sf::RenderTarget& P)
{
	P.draw(this->Text_line4);

}
void GUI::RenderText_line5(sf::RenderTarget& D)
{
	D.draw(this->Text_line5);
}
//Input bar
void GUI::RenderText_input(sf::RenderTarget& O)
{
	O.draw(this->Text_input);
}
void GUI::RenderArrow(sf::RenderTarget& H)
{
	H.draw(this->Arrow);
}
void GUI::RenderSprite(sf::RenderTarget& F) 
{
	F.draw(this->in_game);
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
			std::cout << "GUI::pollEvent You just pressed X" << std::endl;
			this->window->close();
			break;
		//For when press Escape key.
		case sf::Event::KeyPressed:
			if (this->Eve.key.code == sf::Keyboard::Escape)
			{
				std::cout << "GUI::pollEvent You just pressed Escape buttom" << std::endl;
				this->window->close();
			}
			break;
		//Showing current resolutiom if changed.
		case sf::Event::Resized:
			printf("Current resolution:%i,%i\n", Eve.size.width, Eve.size.height);
			break;
		//For entering text.
		case sf::Event::TextEntered:
			this->anyKeyPressed = true;
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

void GUI::AnyInput()
{
	while (this->window->pollEvent(this->Eve)) 
	{
		switch (this->Eve.type)
		{
		case sf::Event::KeyPressed:
			this->anyKeyPressed = true;
			break;
		default:
			break;
		}

	}
}



bool GUI::CheckAnyPress()
{
	return this->anyKeyPressed;
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
	this->anyKeyPressed = false;
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
	//loading font, Map
	if (this->texture.loadFromFile("Resouces/images/Trucksan0.jpg"))
	{
		std::cout << "GUI::text loaded successfully" << std::endl;
	}
	if (this->font.loadFromFile("Resouces/Font/Simple_text.ttf"))
	{
		std::cout << "GUI::font loaded successfully" << std::endl;
	}

	//Setting Input text
	this->Text_input.setFont(this->font);
	this->Text_input.setCharacterSize(23);
	this->Text_input.setFillColor(sf::Color::Black);
	this->Text_input.setPosition(75, 840);
	//Setting Arrow
	this->Arrow.setFont(this->font);
	this->Arrow.setCharacterSize(23);
	this->Arrow.setFillColor(sf::Color::Black);
	this->Arrow.setPosition(50, 840);
	this->Arrow.setString(">");

	//Setting main_ text	
	this->Text_title.setFont(this->font);
	this->Text_title.setCharacterSize(23);
	this->Text_title.setFillColor(sf::Color::Black);
	this->Text_title.setPosition(50, 600);

	this->Text_line1.setFont(this->font);
	this->Text_line1.setCharacterSize(23);
	this->Text_line1.setFillColor(sf::Color::Black);
	this->Text_line1.setPosition(50, 640);

	this->Text_line2.setFont(this->font);
	this->Text_line2.setCharacterSize(23);
	this->Text_line2.setFillColor(sf::Color::Black);
	this->Text_line2.setPosition(50, 680);

	this->Text_line3.setFont(this->font);
	this->Text_line3.setCharacterSize(23);
	this->Text_line3.setFillColor(sf::Color::Black);
	this->Text_line3.setPosition(50, 720);

	this->Text_line4.setFont(this->font);
	this->Text_line4.setCharacterSize(23);
	this->Text_line4.setFillColor(sf::Color::Black);
	this->Text_line4.setPosition(50, 760);

	this->Text_line5.setFont(this->font);
	this->Text_line5.setCharacterSize(23);
	this->Text_line5.setFillColor(sf::Color::Black);
	this->Text_line5.setPosition(50, 800);

	
}


void GUI::InitSprite() 
{
	this->in_game.setTexture(this->texture);
	this->in_game.setPosition(200 ,50);

}

void GUI::InitTexture() 
{
	this->texture.setRepeated(false);
}

void GUI::Update_texture(std::string images) 
{
	if (images == "00") 
	{
		this->texture.loadFromFile("Resouces/images/Trucksan0.jpg");
	}

	else if (images == "01") {
		this->texture.loadFromFile("Resouces/images/Forest01.jpg");
	}
	else if (images == "02") 
	{
		this->texture.loadFromFile("Resouces/images/Excalibur02.png");
	}
	else if (images == "03") 
	{
		this->texture.loadFromFile("Resouces/images/Forestslime03.jpg");
	}
	else if (images == "04") 
	{
		this->texture.loadFromFile("Resouces/images/Bridge04.jpg");
	}
	else if (images == "05") 
	{
		this->texture.loadFromFile("Resouces/images/Houses05.jpg");
	}
	//still no idea about 06
	else if (images == "06")
	{
		this->texture.loadFromFile("Resouces/images/Owner06.jpg");
	}
	else if (images == "07")
	{
		this->texture.loadFromFile("Resouces/images/InHouseRoom07.jpg");
	}
	else if (images == "08")
	{
		this->texture.loadFromFile("Resouces/images/Forest02.jpg");
	}
	else if (images == "09") 
	{
		this->texture.loadFromFile("Resouces/images/Chasm09.jpg");
	}
	else if (images == "10")
	{
		this->texture.loadFromFile("Resouces/images/FrontDoor10.jpg");
	}
	else if (images == "11") 
	{
		this->texture.loadFromFile("Resouces/images/Wallet11.jpg");
	}
	//still no idea about 12
	else if (images == "13") 
	{
		this->texture.loadFromFile("Resouces/images/City13.jpg");
	}
	//no room 14
	else if (images == "15")
	{
		this->texture.loadFromFile("Resouces/images/City15.jpg");
	}
	else if (images == "16")
	{
		this->texture.loadFromFile("Resouces/images/Gabage16.jpg");
	}
	else if (images == "17")
	{
		this->texture.loadFromFile("Resouces/images/Princess17.jpg");
	}
	else if (images == "20")
	{
		this->texture.loadFromFile("Resouces/images/Market20.jpg");
	}
	else if (images == "21")
	{
		this->texture.loadFromFile("Resouces/images/Market20.jpg");
	}
	else if (images == "22")
	{
		this->texture.loadFromFile("Resouces/images/Guild22.jpg");
	}
	else if (images == "23")
	{
		this->texture.loadFromFile("Resouces/images/Exit23.jpg");
	}
}

void GUI::Update_BG(std::string D)
{
	
}

void GUI::ForceClose()
{
	std::cout << std::endl <<"GUI::ForceClose you just force close the game"<<std::endl;
	this->window->close();
}


