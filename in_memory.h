#ifndef IN_MEMORY_H
#define IN_MEMORY_H

#include <string>
#include <vector>
#include "database_interface.h"

class InMemory : public DatabaseInterface {
public:
    
    InMemory();
    ~InMemory() = default;
	bool createNG(const std::string& news_group);
	bool removeNG(int news_group_id);
    std::vector<NewsGroup> listNGs() const;
    std::vector<Article> listArticles(int news_group_id);
	bool addArticle(int news_group_id, const std::string& art_title,
		const std::string& art_author, const std::string& art_text);
	bool removeArticle(int news_group_id, int article_id);
	//Article InMemory::getArticle(int groupId, int artId) const;
    
private:
	std::vector<NewsGroup> news_groups;
};

#endif
