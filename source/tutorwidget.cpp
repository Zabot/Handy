#include "tutorwidget.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <QFont>


using namespace std;

tutorwidget::tutorwidget()
{
 ifstream wordlist("../data/wordList.txt");
 
 string line;
 while (getline(wordlist, line))
 {
 	words.push_back(line);
 }
 wordCount = words.size();
 wordlist.close();

 ifstream siml("../data/similar.txt");
 
 while (getline(siml, line))
 {
 	stringstream ss(line);
	char rep;
	ss >> rep;
	sim.emplace(rep, rep);

	char n;
	while(ss >> n)
	{
		sim.emplace(n, rep);
	}
}
 siml.close();

 this->setGeometry(0,0,600,600);
 this->setStyleSheet("background-color:white;");

 prompt = new QLabel("");
 entered = new QLabel("");
 hint = new QLabel("");
 pixmap = new QPixmap(400, 400);
 newWord();

 QFont f( "Arial", 46, QFont::Bold);
 entered->setFont(f);
 prompt->setFont(f);

 layout = new QVBoxLayout;
 layout->addWidget(prompt);
 layout->setAlignment(prompt, Qt::AlignHCenter);
 layout->addWidget(entered);
 layout->setAlignment(entered, Qt::AlignHCenter);
 layout->addWidget(hint);
 layout->setAlignment(hint, Qt::AlignHCenter);

 this->setLayout(layout);
 this->show();

 connect(this, SIGNAL(procLetter()), this, SLOT(sl()));
}

tutorwidget::~tutorwidget()
{
 delete prompt;
 delete entered;
 delete hint;
 delete pixmap;

 delete layout;
}

void tutorwidget::sl()
{
	string letter = lastLetter;
	if(!debounce)
	{
		if(letterCount < words[(wordCounter % wordCount)].size())
			// If the words have the same rep
			if(sim[letter[0]] == sim[words[(wordCounter % wordCount)].substr(letterCount,1)[0]])
			{
				letter = words[(wordCounter % wordCount)].substr(letterCount,1);
				// Correct
				debounce = true;
				entered->setText(words[(wordCounter % wordCount)].substr(0, ++letterCount).c_str());
				entered->setStyleSheet("QLabel { color : green; }");
				if(letterCount < words[(wordCounter % wordCount)].size())
				{
					startLetter();
					QTimer::singleShot(500, this, SLOT(cooldown()));
				}
				else
					QTimer::singleShot(2500, this, SLOT(newWord()));
			}
			else
			{
				entered->setText((words[(wordCounter % wordCount)].substr(0, letterCount) + letter).c_str());
			}
		if(letterCount == words[(wordCounter % wordCount)].size())
		{
			prompt->setStyleSheet("QLabel { color : green; }");
			entered->setStyleSheet("QLabel { color : green; }");
		}
	}
}

void tutorwidget::setLetter(string letter)
{
	lastLetter = letter;
	emit procLetter();
}


void tutorwidget::cooldown()
{
	debounce = false;
	entered->setStyleSheet("QLabel { color : black; }");
}

void tutorwidget::newWord() {
	debounce = false;
	prompt->setText(getWord().c_str());
	entered->setText("");
	prompt->setStyleSheet("QLabel { color : black; }");
	entered->setStyleSheet("QLabel { color : black; }");
	pixmap->load("/dev/null");
	hint->setPixmap(*pixmap);
	cooldown();
}

void tutorwidget::startLetter()
{
    QTimer::singleShot(0, this, SLOT(assist()));
}

void tutorwidget::assist()
{
	pixmap->load(("../data/signs/"+words[(wordCounter % wordCount)].substr(letterCount,1) + ".png").c_str());
	hint->setPixmap(pixmap->scaledToHeight(300));
}

string tutorwidget::getWord()
{
	startLetter();
	letterCount = 0;
    return words[(++wordCounter) % wordCount];
}



