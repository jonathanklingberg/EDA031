#include <string>
#include <vector>

#include "newsgroup.h"

using namespace std;

NewsGroup::NewsGroup(const string &iTitle) { 
	title = iTitle;
	id = -1;
	index = -1;
}

NewsGroup::~NewsGroup() { }

size_t NewsGroup::size() const { return articles.size(); }

string NewsGroup::getTitle() const { return title; }

void NewsGroup::addArticle(const Article &article) {
	articles.push_back(article);
}

void NewsGroup::deleteArticle(int article_id) {
	size_t i = 0;
	while (i < articles.size()
		&& articles.at(i).getId() != article_id) {
		i++;
	}
	if (i < articles.size()) articles.erase(articles.begin() + i);
}

Article NewsGroup::articleAt(int i) const {
	return articles[i];
}

int NewsGroup::getId() { return id; }

void NewsGroup::setId(int newId) { id = newId; }

int NewsGroup::getIndex() { return index; }

void NewsGroup::setIndex(int newIndex) { index = newIndex; }
