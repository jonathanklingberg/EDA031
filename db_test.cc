#include <string>
#include <iostream>

#include "article.h"
#include "newsgroup.h"
#include "in_memory.h"

using namespace std;

int main() {
	//Test Article
	string art_title_1 = "Kickass article";
	string art_author_1 = "Martin Rydin";
	string art_text_1 = "one two three four five six jnadjnndjnddd cdknjcdkn jkjncd kjncd kjncd";
	Article art_1(art_title_1, art_author_1, art_text_1);
	cout << "Title: " << art_1.getTitle() << endl;
	cout << "Author: " << art_1.getAuthor() << endl;
	cout << "Text: " << art_1.getText() << endl;
	cout << "Index: " << art_1.getIndex() << endl;
	cout << "Id: " << art_1.getId() << endl;
	art_1.setIndex(5);
	art_1.setId(6);
	cout << "Index: " << art_1.getIndex() << endl;
	cout << "Id: " << art_1.getId() << endl;
	
	//InMemory
	InMemory db;
	
	//----------- createNG-test
	
	bool successfull;
	
	string ng_name;
	ng_name = "aftonbladet";
	successfull = db.createNG(ng_name);
	if (successfull) cout << "nice! aftonbladet created" << endl;
	
	ng_name = "DN";
	successfull = db.createNG(ng_name);
	if (successfull) cout << "nice! DN created" << endl;
	
	ng_name = "aftonbladet";
	successfull = db.createNG(ng_name);
	if (!successfull) cout << "nice! aftonbladet not created" << endl;
	
	//------------- listNGs-test
	
	vector<NewsGroup> ngs = db.listNGs();
	cout << "Size should be 2. It is " << ngs.size() << endl;
	
	for (NewsGroup ng : ngs) {
		cout << "Name: " << ng.getTitle() << ". ID is: " << ng.getId() << endl;
	}
    ngs = db.listNGs();
    cout<<"size of ngs is "<<ngs.size()<<endl;
    for(NewsGroup ng : ngs){
        if(db.addArticle(ng.getId(),"hej0sjsfsjhfsffffffjfjfjfjfjfjfjfjfjjfjfjfjfjffjfjfjfjfjfisjfisfjsifjsifjsifjsifjsifjsfijsfijsfijsfisjfisjfsifjsifjsifjsifjsifjsifjsfijsfisjfisjfsifjsifjsifjsifjsfisjfisjfisfjsifjsifjsifjsifjsfijsfisjfisjfsifjsifjsfijsifjsifjsifj","hej2","hej3")){
            cout<<"article added to group "<<ng.getId()<<endl;
        }else{
            cout<<"article could not be added to group "<<ng.getId()<<endl;
        }
    }
    ngs = db.listNGs();
    for(NewsGroup ng : ngs){
        vector<Article> arts = db.listArticles(ng.getId());
        for(Article a : arts){
            cout << "hej hittade artikeln "<<"ID: "<<a.getId()<<" "<<"TITLE "<<a.getTitle()<<"AUTHOR: "<<a.getAuthor()<<" TEXT: "<<a.getText()<<endl;
        }
    }
	
    //	//-------------- removeNG-test
    //
    //	db.removeNG(0);
    //	ngs = db.listNGs();
    //	cout << "Size should be 1. It is " << ngs.size() << endl;
    //	
    //	//-------------- 
	
}