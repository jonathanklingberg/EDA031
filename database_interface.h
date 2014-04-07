/*
 * Interface DatabaseInterface -- all database implementations must
 * implement this interface.
 */
#ifndef DATABASE_INTERFACE_H
#define DATABASE_INTERFACE_H

#include <string>
#include <vector>

#include "article.h"
#include "newsgroup.h"

class DatabaseInterface {
public:
	virtual ~DatabaseInterface() = default;
    
    DatabaseInterface(){}
	
	/*
	 * Create a newsgroup. Returns false if NewsGroup already exists.
	 */
	virtual bool createNG(const std::string& news_group) = 0;
	
	/*
	 * Removes newsgroup. Returns true if newsgroup was deleted and
	 * false if the newsgroup doesn't exist.
	 */
	virtual bool removeNG(int news_group_id) = 0;
	
	/*
	 * Lists all newsgroups. Returns array of newsgroups. If no newsgroups
	 * exists an empty array is returned.
	 */
	virtual std::vector<NewsGroup> listNGs() const = 0;
	
	/*
	 * Lists all articles in specified newsgroup. Returns array of newsgroups. 
	 * If no newsgroups exists an empty array is returned.
	 */
	virtual std::vector<Article> listArticles(int news_group_id) = 0;
	
	/* 
	 * Adds new article in specified NewsGroup. Returns false
	 * if newsgroup doesn't exists.
	 */
	virtual bool addArticle(int news_group_id, const std::string& art_title, 
		const std::string& art_author, const std::string& art_text) = 0;
	 
	/* 
	 * Adds new article in specified NewsGroup. Returns false
	 * if newsgroup doesn't exists.
	 */
	virtual bool removeArticle(int news_group_id, int article_id) = 0;
	 
};

#endif