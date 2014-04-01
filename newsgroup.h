#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>
#include <vector>

#include "article.h"

class NewsGroup {

public:
	NewsGroup(const std::string &title);
	~NewsGroup();
	size_t size() const;
	std::string getTitle() const;
	void addArticle(const Article &article);
	void deleteArticle(int article_id);
	Article articleAt(int i) const;
	int getId();
	void setId(int newId);
	int getIndex();
	void setIndex(int newIndex);
    
    std::vector<Article> articles;

private:
	std::string title;
	int id;
	int index;
	
};

#endif