#include "in_memory.h"
#include <string>
#include <vector>

using namespace std;


InMemory::InMemory() {}

bool InMemory::createNG(const string& news_group_name) {
	for (unsigned i = 0; i < news_groups.size(); ++i) {
		NewsGroup &ng = news_groups.at(i)
		if (ng.getId() > -1 && ng.getTitle().compare(news_group_name)) return false;
	}
	NewsGroup new_group;
	new_group(news_group_name);
	new_group.setId(news_groups.size()); 
	news_groups.push_back(new_group);
	return true;
}
	
bool InMemory::removeNG(int news_group_id) {
	for (unsigned i = 0; i < news_groups.size(); ++i) {
    	if (ng.getId() == news_groups.at(i).getId()) {
    		news_groups.at(i).setId(-1);
    		return true;
    	}
    }
	return false;
}
	
vector<NewsGroup> InMemory::listNGs() const {
	vector<NewsGroup> ngs;
	for (unsigned i = 0; i < news_groups.size(); ++i) {
		NewsGroup &ng = news_groups.at(i);
    	if (ng.getId() > -1) {
    		ngs.push_back(ng);
    	}
    }
	return ngs;
}
	
vector<Article> InMemory::listArticles(int news_group_id) const {
	vector<Article> articles;
	for (unsigned i = 0; i < news_groups.size(); ++i) {
		NewsGroup &ng = news_groups.at(i);
    	if (ng.getId() == news_group_id) {
    		int g = 0;
    		for (size_t s = 0; s < ng.size(); ++s) {
    			Article &art = ng.articleAt(g);
    			if (art.getId() > -1) articles.push_back(art);
    			++g;
    		}
    	}
    }
	return articles;
}
	
bool InMemory::addArticle(int news_group_id, const string& art_title, 
		const string& art_author, const string& art_text) {
	
}
	
bool InMemory::removeArticle(int news_group_id, int article_id) {
	for (unsigned i = 0; i < news_groups.size(); ++i) {
		if (news_group.getId() == news_groups.at(i)) {
			NewsGroup &ng = news_groups.at(i);
			for ()
		}
	}
}
	
NewsGroup InMemory::groupAt(int id) const {
	NewsGroup ng;
	for (unsigned i = 0; i < news_groups.size(); ++i) {
		if (news_groups.at(i).getId() == id) {
			ng = news_groups.at(i);
		}
	}
	return ng;
}
	
	
	
	
	
