#ifndef IN_MEMORY_H
#define IN_MEMORY_H

#include <string>
#include <vector>
#include "database_interface.h"

using namespace std;
class InMemory : public DatabaseInterface {
public:
    InMemory();
	virtual bool createNG(const string& news_group);
	virtual bool removeNG(int news_group_id);
    vector<NewsGroup> listNGs() const;
    vector<Article> listArticles(int news_group_id) const;
	virtual bool addArticle(int news_group_id, const string& art_title,
		const string& art_author, const string& art_text);
	virtual bool removeArticle(int news_group_id, int article_id);
    
private:
	vector<NewsGroup> news_groups;
};

#endif