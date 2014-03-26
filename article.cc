#include <string>

#include "article.h"

using namespace std;

Article::Article(string ititle, string iauthor, string itext) {
	title = ititle;
	author = iauthor;
	text = itext;
	id = -1;
	index = -1;
}

Article::~Article() {}

string Article::getTitle() const { return title; }

string Article::getAuthor() const { return author; }

string Article::getText() const { return text; }

int Article::getId() const { return id; }

void Article::setId(const int newId) { id = newId; }

int Article::getIndex() const { return index; }

void Article::setIndex(const int newIndex) { index = newIndex; }