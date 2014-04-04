#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>
#include <vector>

#include "article.h"

class NewsGroup {

public:
	NewsGroup(const std::string &title);
	~NewsGroup();
	int size() const;
	std::string getTitle() const;
	void addArticle(Article &article);
	void deleteArticle(int article_id);
	Article articleAt(int i) const;
    std::vector<Article> getArticles();
	int getId();
	void setId(int newId);
	int getIndex();
	void setIndex(int newIndex);
    bool articleExists(int article_id);
    
    std::vector<Article> articles;

private:
	std::string title;
	int id;
	int index;
	
};

#endif