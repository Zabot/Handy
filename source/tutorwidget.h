#ifndef TUTORWIDGET_H
#define TUTORWIDGET_H

#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QTimer>
#include <QPixmap>

#include <string>
#include <vector>
#include <map>

class tutorwidget : public QWidget
{
Q_OBJECT

public:
    tutorwidget();
    ~tutorwidget();
    void setLetter(std::string l);

private:
    std::string getWord();
    void startLetter();

private:
    QLabel *prompt;
    QLabel *entered;
	QLabel *hint;
	QPixmap *pixmap;

	std::vector<std::string> words;

    QVBoxLayout *layout;
	unsigned int wordCounter = -1;
	unsigned int wordCount;
    std::string lastLetter;
    unsigned int consec = 0;
	unsigned int letterCount = 0;
	bool debounce = false;

	std::map<char, char> sim;

public slots:
    void assist();
	void newWord();
	void cooldown();
	void sl();

signals:
	void procLetter();

};

#endif // TUTORWIDGET_H

