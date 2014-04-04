#include <string>
#include <vector>

#include "newsgroup.h"

using namespace std;

NewsGroup::NewsGroup(const string &iTitle) { 
	title = iTitle;
	id = -1;
	index = -1;
    articles.clear();
}

NewsGroup::~NewsGroup() { }

int NewsGroup::size() const {
    size_t size = articles.size();
    int res(size);
    return res;
}

string NewsGroup::getTitle() const { return title; }

void NewsGroup::addArticle(Article &article) {
    article.setId(articles.size());
	articles.push_back(article);
}

void NewsGroup::deleteArticle(int article_id) {
	size_t i = 0;
	while (i < articles.size()
		&& articles.at(i).getId() != article_id) {
		++i;
	}
	if (i < articles.size()){
        articles.erase(articles.begin() + i);
        //articles[i].setId(-1);
    }
}

Article NewsGroup::articleAt(int i) const {
	return articles[i];
}

vector<Article> NewsGroup::getArticles(){
    return articles;
}


int NewsGroup::getId() { return id; }

void NewsGroup::setId(int newId) { id = newId; }

int NewsGroup::getIndex() { return index; }

void NewsGroup::setIndex(int newIndex) { index = newIndex; }
