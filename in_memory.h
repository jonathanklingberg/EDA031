#ifndef IN_MEMORY_H
#define IN_MEMORY_H

#include "database_interface.h"

class InMemory {
public:
	bool createNG(const NewsGroup&);
	bool removeNG(const NewsGroup&);
	NewsGroup[] listNGs() const;
	Article[] listArticles(const NewsGroup&) const;
	bool addArticle(const NewsGroup&, const Article&);
	bool removeArticle(const NewsGroup&, const Article&);	
};

#endif