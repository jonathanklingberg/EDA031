/*
 * Interface DatabaseInterface -- all database implementations must
 * implement this interface.
 */
#ifndef DATABASE_INTERFACE_H
#define DATABASE_INTERFACE_H

#include <string>

using NewsGroup = std::string;
using Article = std::string;

class DatabaseInterface {
public:
	virtual ~DatabaseInterface() = default;
	
	/*
	 * Create a newsgroup. Returns false if NewsGroup already exists.
	 */
	virtual bool createNG(const NewsGroup&) = 0;
	
	/*
	 * Removes newsgroup. Returns true if newsgroup was deleted and
	 * false if the newsgroup doesn't exist.
	 */
	virtual bool removeNG(const NewsGroup&) = 0;
	
	/*
	 * Lists all newsgroups. Returns array of newsgroups. If no newsgroups
	 * exists an empty array is returned.
	 */
	virtual NewsGroup[] listNGs() = 0;
	
	/*
	 * Lists all articles in specified newsgroup. Returns array of newsgroups. 
	 * If no newsgroups exists an empty array is returned.
	 */
	virtual Article[] listArticles(const NewsGroup&) = 0;
	
	/* 
	 * Adds new article in specified NewsGroup. Returns false
	 * if newsgroup doesn't exists.
	 */
	 virtual bool addArticle(const NewsGroup&, const Article&) = 0;
	 
	/* 
	 * Adds new article in specified NewsGroup. Returns false
	 * if newsgroup doesn't exists.
	 */
	 virtual bool removeArticle(const NewsGroup&, const Article&) = 0;	
};

#endif