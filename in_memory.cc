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
	vector<Article> articles;
    auto it = find_if((newsgroups.begin()), newsgroups.end(), [&groupId](NewsGroup ng){ return ng.getId() == groupId;});
    if(it2 != newsgroups.end()) {
        sch.writeAnswer(Protocol::ANS_ACK);
        vector<Article> articles = db->listArticles(groupId);
        sch.writeAnswer(Protocol::PAR_NUM);
        sch.writeNumber(articles.size());                 //Antal artiklar
        for(size_t i = 0; i < articles.size(); ++i) {
            sch.writeAnswer(Protocol::PAR_NUM);
            sch.writeNumber(articles[i].getId());
            sch.writeAnswer(Protocol::PAR_STRING);
            sch.writeNumber(articles[i].getTitle().size());
            sch.writeString(articles[i].getTitle());

//	for (size_t i = 0; i < news_groups.size(); ++i) {
//		NewsGroup ng = news_groups[i];
//    	if (ng.getId() == news_group_id) {
//            
//    		int g = 0;
//    		for (size_t s = 0; s < ng.size(); ++s) {
//    			Article &art = ng.articleAt(g);
//    			if (art.getId() > -1) articles.push_back(art);
//    			++g;
//    		}
//    	}
//    }
	return articles;
}
	
//bool InMemory::addArticle(int news_group_id, const string& art_title,
//		const string& art_author, const string& art_text) {
//	
//}
//	
//bool InMemory::removeArticle(int news_group_id, int article_id) {
//	for (unsigned i = 0; i < news_groups.size(); ++i) {
//		if (news_group.getId() == news_groups.at(i).getId()) {
//			NewsGroup &ng = news_groups.at(i);
//			ng.deleteArticle(article_id);
//			return true;
//		}
//	}
//	return false;
//}
//	
//NewsGroup InMemory::groupAt(int id) const {
//	NewsGroup ng;
//	for (unsigned i = 0; i < news_groups.size(); ++i) {
//		if (news_groups.at(i).getId() == id) {
//			ng = news_groups.at(i);
//		}
//	}
//	return ng;
//}

	
	
	
	
