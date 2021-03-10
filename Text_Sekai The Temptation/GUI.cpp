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

void GUI::UpdateText(std::string s1)
{
	std::stringstream ss;
	ss << s1;
	this->main_info.setString(ss.str());
}


/*
	Rendering Function
*/
void GUI::Render()
{
	this->window->clear(sf::Color::White);
	//this->window->draw(info);
	//this->window->draw(in_arrow);
	this->RenderText(*this->window);

	this->window->display();
}

void GUI::RenderText(sf::RenderTarget &T)
{
	T.draw(this->main_info);
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
				std::cout << "Event::Eve You just pressed Escape buttom" << std::endl;
				this->window->close();
			break;

		//For entering text.
		//case sf::Event::TextEntered:
				//if (Eve.text.unicode >= 32 && Eve.text.unicode <= 126 && sentence.getSize() < 20) // รับอินพุทต์แค่ 32 - 126 ในตารางยูนิโค้ดและจำกัดมันไว้แค่ 20 ตัวอักษร
				//{
				//	sentence += (char)Eve.text.unicode; // ใส่ตัวอักษร char ทีละตัวลงไป
				//}
				//else if (Eve.text.unicode == 8 /*Delete key*/ && sentence.getSize() >= 0) // ลบตัวอักษร
				//{
				//	sentence.erase(sentence.getSize() - 1, sentence.getSize()); // ลบตามขนาดลงไปทีละตัว
				//}
				//else if (Eve.text.unicode == 13/*Enter key*/ && sentence.getSize()) // กด ENTER 
				//{
				//	for (unsigned int i = 0; i < sentence.getSize(); i++)
				//	{
				//		putchar(tolower(sentence[i]));
				//	}
				//}

		default:
			break;
		}
	}
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
	this->window = new sf::RenderWindow(this->videomode, "Text Adventure", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(30);
}

void GUI::InitText()
{	
	//loading font
	if(this->font.loadFromFile("Resouces/Font/Simple_text.ttf"))
	{
		std::cout << "GUI::font loaded successfully"<<std::endl;
	}

	//Setting testing text	
	this->main_info.setFont(this->font);
	this->main_info.setCharacterSize(23);
	this->main_info.setFillColor(sf::Color::Black);
	this->main_info.setPosition(50, 200);


	/*
	info.setString("Testing");
	info.setPosition(0, 600);
	info.setCharacterSize(23);
	info.setFillColor(sf::Color::Black);

	in_arrow.setString("> ");
	in_arrow.setPosition(0, 800);
	in_arrow.setCharacterSize(23);
	in_arrow.setFillColor(sf::Color::Black);
	*/
}