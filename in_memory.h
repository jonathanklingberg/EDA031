#ifndef IN_MEMORY_H
#define IN_MEMORY_H

#include <string>
#include <vector>
#include "database_interface.h"

class InMemory {
public:
	bool createNG(const NewsGroup&);
	bool removeNG(const NewsGroup&);
	std::vector<NewsGroup> listNGs() const;
	std::vector<Article> listArticles(const NewsGroup&) const;
	bool addArticle(const NewsGroup&, const Article&);
	bool removeArticle(const NewsGroup&, const Article&);
private:
	std::vector<std::vector<Article>> news_groups;
};

#endif