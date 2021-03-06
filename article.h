#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article {

public:
	Article(std::string title, std::string author, std::string text);
	~Article();
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getText() const;
	int getId() const;
	void setId(const int newId);

private:
	std::string title;
	std::string author;
	std::string text;
	int id;

};

#endif