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
}

/*
	Accessor
*/

const bool GUI::Running() const
{
	return this->window->isOpen();
}



/*
	displaying definition
*/
void GUI::Update()
{
	this->pollEvent();
}


void GUI::Render()
{
	window->clear();
	window->draw(info);
	window->draw(in_arrow);
	window->display();
}

/*
	Poll Event
*/

void GUI::pollEvent()
{
	//Event polling
	while (this->window->pollEvent(this->Eve))
	{
		switch (this->Eve.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::TextEntered:
				if (Eve.text.unicode >= 32 && Eve.text.unicode <= 126 && sentence.getSize() < 20) // รับอินพุทต์แค่ 32 - 126 ในตารางยูนิโค้ดและจำกัดมันไว้แค่ 20 ตัวอักษร
				{
					sentence += (char)Eve.text.unicode; // ใส่ตัวอักษร char ทีละตัวลงไป
				}
				else if (Eve.text.unicode == 8/*Delete key*/ && sentence.getSize() >= 0) // ลบตัวอักษร
				{
					sentence.erase(sentence.getSize() - 1, sentence.getSize()); // ลบตามขนาดลงไปทีละตัว
				}
				else if (Eve.text.unicode == 13/*Enter key*/ && sentence.getSize()) // กด ENTER 
				{
					for (unsigned int i = 0; i < sentence.getSize(); i++)
					{
						putchar(tolower(sentence[i]));
					}
				}

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
	info.setString("Testing");
	info.setPosition(0, 600);
	info.setCharacterSize(23);
	info.setFillColor(sf::Color::Black);

	in_arrow.setString("> ");
	in_arrow.setPosition(0, 800);
	in_arrow.setCharacterSize(23);
	in_arrow.setFillColor(sf::Color::Black);
}