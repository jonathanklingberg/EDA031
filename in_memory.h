#ifndef IN_MEMORY_H
#define IN_MEMORY_H

#include <string>
#include <vector>
#include "database_interface.h"

class InMemory : public DatabaseInterface {
public:
	InMemory();
	virtual bool createNG(const std::string& news_group);
	virtual bool removeNG(int news_group_id);
	virtual std::vector<NewsGroup> listNGs() const;
	virtual std::vector<Article> listArticles(int news_group_id) const;
	virtual bool addArticle(int news_group_id, const std::string& art_title, 
		const std::string& art_author, const std::string& art_text);
	virtual bool removeArticle(int news_group_id, int article_id);
	virtual NewsGroup groupAt(int i) const;
private:
	std::vector<std::vector<NewsGroup>> news_groups;
};

#endif