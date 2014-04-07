#include "in_memory.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

InMemory::InMemory(){}

bool InMemory::createNG(const string& news_group_name) {
    
    //auto it = find_if((news_groups.begin()), news_groups.end(), [&news_group_name](NewsGroup ng) { return ng.getTitle() == news_group_name;});
    for(NewsGroup ng : news_groups) {
        if(ng.getTitle() == news_group_name && ng.getId() > -1) {
            return false;
        }
    }
    NewsGroup news_group(news_group_name);
    news_group.setId(news_groups.size());
    news_groups.push_back(news_group);
	return true;
}

bool InMemory::removeNG(int news_group_id) {
    //for(NewsGroup ng : news_groups) {
    for(size_t i = 0; i != news_groups.size(); ++i){
        //if(ng.getId() == news_group_id) {
        if(news_groups[i].getId() == news_group_id){
            news_groups[news_group_id].setId(-1);
            //ng.setId(-1);
            return true;
        }
    }
    return false;
}

vector<NewsGroup> InMemory::listNGs() const{
	vector<NewsGroup> ngs;
    for(NewsGroup ng: news_groups){
        if(ng.getId() > -1){
            ngs.push_back(ng);
        }
    }
    return ngs;
}

vector<Article> InMemory::listArticles(int news_group_id){
    cout<<"entered list articles"<<endl;
    vector<Article> res;
    //vector<NewsGroup> ngs = listNGs();
    //--edit--
 
    vector<NewsGroup> ngs;
    for(NewsGroup ng: news_groups){
        ngs.push_back(ng);
    }

    //--edit--
    //for(NewsGroup ng : ngs) {
    for(size_t i = 0; i != news_groups.size(); ++i){
        cout<<news_groups[i].getId()<<" should match "<<news_group_id<<endl;
        //if(ng.getId() == news_group_id) {
        if(news_groups[i].getId() == news_group_id){
            cout<<"pass id test"<<endl;
            //int size = ngs[news_group_id].size();
            //cout <<"size: "<<size<<endl;
            cout<<"hej här funkar det"<<endl;
            res = ngs[news_group_id].getArticles();
            //return ngs[ng.getId()].getArticles();
        }
    }
    return res;

           // arts = ngs[news_group_id].getArticles();
//            cout<<arts.size()<<endl;
//            for(Article a : arts) {
//                cout << "first article in ng"<<endl;
//                cout<<a.getId()<<endl;
//                if(a.getId() > -1){
//                    cout<<"article id was > -1"<<endl;
//                    res.push_back(a);
//                }else{
//                    cout<<"article id was < -1"<<endl;
//                }
//            }
//        }else{
//            cout<<"fail"<<endl;
//        }
//    }
//    return res;
}

bool InMemory::addArticle(int news_group_id, const string& art_title,
                          const string& art_author, const string& art_text) {
    vector<NewsGroup> ngs = listNGs();
    for(NewsGroup ng : ngs ) {
        if(ng.getId() == news_group_id){
            Article art(art_title,art_author,art_text);
            news_groups[news_group_id].addArticle(art);
            return true;
        }
    }
    return false;
}

bool InMemory::removeArticle(int news_group_id, int article_id) {
	for (size_t i = 0; i < news_groups.size(); ++i) {
		if (news_group_id == news_groups[i].getId()) {
            if(news_groups[i].articleExists(article_id)){
			news_groups[news_group_id].deleteArticle(article_id);
            cout<<"deleted article"<<endl;
            cout<<"size of articles "<<news_groups[news_group_id].size()<<endl;
			return true;
		}
            return false;
        }
	}
	return false;
}


Article InMemory::getArticle(int groupId, int artId) {
	vector<Article> arts = listArticles(groupId);
            return arts[artId];
//		for(Article a : arts) {
//		 	if(a.getId() == artId) {
//				return a;
//			}
		}

bool InMemory::artExists(int groupId,int artId){
    vector<Article> arts = listArticles(groupId);
    for(size_t i = 0; i != arts.size(); ++i){
        if(arts[i].getId() == artId){
            return true;
        }
    }
    return false;
}







