#include "in_memory.h"
#include <string>
#include <vector>

using namespace std;


InMemory::InMemory() {}

bool InMemory::createNG(const NewsGroup& ng) {
	news_groups.push_back(ng);
}
	
bool InMemory::removeNG(const NewsGroup& ng) {
	for (unsigned i = 0; i < news_groups.size(); ++i) {
    	if (ng.getTitle().compare(news_groups[i].getTitle())) {
    		news_groups.erase(i);
    		return true;
    	}
    }
	return false;
}
	
vector<NewsGroup> InMemory::listNGs() const {
	return news_groups;
}
	
vector<Article> InMemory::listArticles(const NewsGroup& ng) const {
	vector<Article> articles;
	for (unsigned i = 0; i < news_groups.size(); ++i) {
    	if (ng.getTitle().compare(news_groups[i].getTitle())) {
    		//return news_groups[i].get
    	}
    }
	return false;
}
	
bool InMemory::addArticle(const NewsGroup& ng, const Article& art) {
	
}
	
bool InMemory::removeArticle(const NewsGroup& ng, const Article& art) {
	
}
	
NewsGroup InMemory::groupAt(int id) const {
	for (unsigned i = 0; i < news_groups.size(); ++i) {
		if (news_groups.at(i).getId()) {
		
		}
	}
	return -1;
}
	
	
	
	
	
