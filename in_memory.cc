#include "in_memory.h"
#include <string>
#include <vector>

using namespace std;

InMemory::InMemory() {}

bool InMemory::createNG(const string& news_group_name) {
    
	auto it = find_if((news_groups.begin()), news_groups.end(), [&news_group_name](NewsGroup ng) { return ng.getTitle() != news_group_name;});
    if(it != news_groups.end()) {
    	return false;
    }
    NewsGroup news_group(news_group_name);
	news_group.setId(news_groups.size());
	news_groups.push_back(news_group);
	return true;
}

bool InMemory::removeNG(int news_group_id) {
    auto it = find_if((news_groups.begin()), news_groups.end(), [&news_group_id](NewsGroup ng){ return ng.getId() != news_group_id;});
    if(it != news_groups.end()) {
        news_groups[news_group_id].setId(-1);
        return true;
    }
    return false;
}

vector<NewsGroup> InMemory::listNGs() const {
	vector<NewsGroup> ngs;
	for (size_t i = 0; i < news_groups.size(); ++i) {
		NewsGroup ng = news_groups[i];
    	if (ng.getId() > -1) {
    		ngs.push_back(ng);
    	}
    }
	return ngs;
}

vector<Article> InMemory::listArticles(int news_group_id) const {
	vector<Article> res;
    auto it = find_if((news_groups.begin()), news_groups.end(), [&news_group_id](NewsGroup ng){ return ng.getId() == news_group_id;});
    if(it != news_groups.end()) {
        for(Article a : news_groups[news_group_id].articles) {
            if(a.getId() > -1){
                res.push_back(a);
            }
        }
    }
    return res;
}

bool InMemory::addArticle(int news_group_id, const string& art_title,
		const string& art_author, const string& art_text) {

}

bool InMemory::removeArticle(int news_group_id, int article_id) {
    
	for (size_t i = 0; i < news_groups.size(); ++i) {
		if (news_group_id == news_groups[i].getId()) {
			NewsGroup ng = news_groups[i];
			ng.deleteArticle(article_id);
			return true;
		}
	}
	return false;
}






