#ifndef ON_DISK_H
#define ON_DISK_H

#include <string>
#include <vector>
#include "database_interface.h"

class OnDisk : public DatabaseInterface {
public:
    
    OnDisk();
    ~OnDisk() = default;
	bool createNG(const std::string& news_group);
	bool removeNG(int news_group_id);
    std::vector<NewsGroup> listNGs() const;
    std::vector<Article> listArticles(int news_group_id);
	bool addArticle(int news_group_id, const std::string& art_title,
		const std::string& art_author, const std::string& art_text);
	bool removeArticle(int news_group_id, int article_id);
    
private:
	std::vector<NewsGroup> news_groups;
	int getNextIndex();
	std::vector<NewsGroup> listAllIds() const;
	std::vector<Article> listAllArticleIds(std::string& path) const;
	Article readArticle(std::string& path, int file_id) const;
	void writeToNGList(std::vector<NewsGroup>& ngs);
	void writeToArticleList(std::vector<Article>& arts, std::string& path);
	void writeToArticle(Article& art, std::string& path);
};

#endif