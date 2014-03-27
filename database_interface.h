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
	
	/*
	 * Create a newsgroup. Returns false if NewsGroup already exists.
	 */
	virtual bool createNG(const NewsGroup& ng) = 0;
	
	/*
	 * Removes newsgroup. Returns true if newsgroup was deleted and
	 * false if the newsgroup doesn't exist.
	 */
	virtual bool removeNG(const NewsGroup& ng) = 0;
	
	/*
	 * Lists all newsgroups. Returns array of newsgroups. If no newsgroups
	 * exists an empty array is returned.
	 */
	virtual std::vector<NewsGroup> listNGs() = 0;
	
	/*
	 * Lists all articles in specified newsgroup. Returns array of newsgroups. 
	 * If no newsgroups exists an empty array is returned.
	 */
	virtual std::vector<Article> listArticles(const NewsGroup& ng) = 0;
	
	/* 
	 * Adds new article in specified NewsGroup. Returns false
	 * if newsgroup doesn't exists.
	 */
	virtual bool addArticle(const NewsGroup& ng, const Article& art) = 0;
	 
	/* 
	 * Adds new article in specified NewsGroup. Returns false
	 * if newsgroup doesn't exists.
	 */
	virtual bool removeArticle(const NewsGroup& ng, const Article& art) = 0;
	 
	/*
	 * Gets group with the specified id. Return a ng with id set to -1 if not exist.
	 */ 
	virtual NewsGroup groupAt(int i) = 0;
};

#endif