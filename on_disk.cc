#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "on_disk.h"
#include "on_disk.h"


using namespace std;

OnDisk::OnDisk(){
	string root = "db";
	string ng = "db/newsgroups";
	if(!mkdir(root.c_str(),0755)) {
		ofstream file(ng);
		file << "1 <next_id>" << endl;
		file.close();
	}
}

bool OnDisk::createNG(const string& news_group_name) {
	NewsGroup tmp(news_group_name);
	for (NewsGroup ng : listNGs()) {
		if (!ng.getTitle().compare(news_group_name)) {
			return false;
		}
	}
	vector<NewsGroup> all_ngs = listAllIds();
	vector<NewsGroup> new_ngs;
	for (NewsGroup ng : all_ngs) {
		if (!ng.getTitle().compare("<next_id>")) tmp.setId(ng.getId());
		else new_ngs.push_back(ng);
	}
	new_ngs.push_back(tmp);
	NewsGroup new_next("<next_id>");
	new_next.setId(tmp.getId() + 1);
	new_ngs.push_back(new_next);
	writeToNGList(new_ngs);
	string path = "db/";
	path += to_string(tmp.getId());
	if(!mkdir(path.c_str(),0755)) {
		path += "/articles";
		ofstream file(path);
		file << "1 <next_id>" << endl;
		file.close();
	}
	return true;
}

bool OnDisk::removeNG(int news_group_id) {
	bool exist = false;
	for (NewsGroup ng : listNGs()) {
		if (ng.getId() == news_group_id) {
			exist = true;
		}
	}
	if (!exist) return false;
	vector<NewsGroup> all_ngs = listAllIds();
	vector<NewsGroup> new_ngs;
	NewsGroup tmp("<deleted_ng>");
	for (NewsGroup ng : all_ngs) {
		if (ng.getId() == news_group_id) {
			tmp.setId(ng.getId());
			new_ngs.push_back(tmp);
		}
		else new_ngs.push_back(ng);
	}
	writeToNGList(new_ngs);
	string path = "db/";
	path += to_string(news_group_id);
	//remove_dir();
	return true;
}

vector<NewsGroup> OnDisk::listNGs() const {
	vector<NewsGroup> all_ngs = listAllIds();
	vector<NewsGroup> ngs;
	for(NewsGroup ng : all_ngs) {
		string title = ng.getTitle();
		if (title.compare("<deleted_ng>") && title.compare("<next_id>")) ngs.push_back(ng);		
	}
	return ngs;
}

vector<Article> OnDisk::listArticles(int news_group_id) {
	vector<Article> arts;
	vector<NewsGroup> ngs = listNGs();
	bool exist = false;
	for (NewsGroup ng : ngs) if (ng.getId() == news_group_id) exist = true;
	if (!exist) return arts;
	string path = to_string(news_group_id);
	vector<Article> all_arts = listAllArticleIds(path);
	
	for(Article art : all_arts) {
		string title = art.getTitle();
		if (title.compare("<deleted_art>") && title.compare("<next_id>")) {
			arts.push_back(readArticle(path, art.getId()));
		}
	}
	return arts;
}

bool OnDisk::addArticle(int news_group_id, const string& art_title,
		const string& art_author, const string& art_text) {
	string path = to_string(news_group_id);
	vector<Article> all_arts = listAllArticleIds(path);
	vector<Article> new_arts;
	Article tmp(art_title, art_author, art_text);
	for (Article art : all_arts) {
		if (!art.getTitle().compare("<next_id>")) {
			tmp.setId(art.getId());
			new_arts.push_back(tmp);
		} else {
			new_arts.push_back(art);
		}
	}
	Article next_id("<next_id>", "n/a", "n/a");
	next_id.setId(tmp.getId() + 1);
	new_arts.push_back(next_id);
	writeToArticleList(new_arts, path);
	writeToArticle(tmp, path);
	return true;
}

bool OnDisk::removeArticle(int news_group_id, int article_id) {
	bool exist = false;
	for (Article art : listArticles(news_group_id)) {
		if (art.getId() == article_id) {
			exist = true;
		}
	}
	if (!exist) return false;
	string path = to_string(news_group_id);
	vector<Article> all_arts = listAllArticleIds(path);
	vector<Article> new_arts;
	Article tmp("<deleted_art>", "n/a", "n/a");
	for (Article art : all_arts) {
		if (art.getId() == article_id) {
			tmp.setId(art.getId());
			new_arts.push_back(tmp);
		}
		else new_arts.push_back(art);
	}
	writeToArticleList(new_arts, path);
	return true;
}

//---- Help-functions ----

int OnDisk::getNextIndex() {
	int next = 0;
	for (NewsGroup ng : listAllIds()) if (ng.getTitle().compare("<next_id>")) next = ng.getId();
	return next;
}

vector<NewsGroup> OnDisk::listAllIds() const {
	vector<NewsGroup> ngs;
	ifstream infile("db/newsgroups");
	if (infile.good()) {
		string sLine;
		while(getline(infile, sLine)) {
			stringstream  stream(sLine);
			string  s_id, ng_name;
			stream >> s_id;
			getline(stream, ng_name);
			ng_name = ng_name.substr(1); 
			NewsGroup ng(ng_name);
			int id = atoi(s_id.c_str());
			ng.setId(id);
			ngs.push_back(ng);
			stream.clear();
		}
	}
	infile.close();
	return ngs;
}

vector<Article> OnDisk::listAllArticleIds(string& path) const {
	vector<Article> arts;
	string bull = "n/a";
	string art_path = "db/";
	art_path += path;
	art_path += "/articles";
	ifstream infile(art_path);
	if (infile.good()) {
		string sLine;
		while(getline(infile, sLine)) {
			stringstream  stream(sLine);
			string  s_id, s_title;
			stream >> s_id;
			
			getline(stream, s_title);
			s_title = s_title.substr(1);
			
			Article art(s_title, bull, bull);
			int id = atoi(s_id.c_str());
			art.setId(id);
			arts.push_back(art);
			stream.clear();
		}
	}
	infile.close();
	return arts;
}

Article OnDisk::readArticle(string& path, int file_id) const {
	string art_path = "db/";
	art_path += path;
	art_path += "/";
	art_path += to_string(file_id);
	string s_title = "n/a", s_author = "n/a", s_text = "n/a";
	
	ifstream infile(art_path);
	if (infile.good()) {
		string sline;
		
		getline(infile, s_title);
		getline(infile, s_author);
		getline(infile, s_text);
		while(getline(infile, sline)) {
			s_text += "\n";
			s_text += sline;
			
		}
	}
	
	Article art(s_title, s_author, s_text);
	art.setId(file_id);
	infile.close();
	return art;
}

void OnDisk::writeToNGList(vector<NewsGroup>& ngs) {
	string ng_path = "db/newsgroups"; 
	ofstream file(ng_path);
	for (NewsGroup ng : ngs) {
		file << ng.getId() << " " << ng.getTitle() << endl;
	}
	file.close();
}

void OnDisk::writeToArticleList(vector<Article>& arts, string& path) {
	string art_path = "db/";
	art_path += path;
	art_path += "/articles";
	ofstream file(art_path);
	for (Article art : arts) {
		file << art.getId() << " " << art.getTitle() << endl;
	}
	file.close();
}

void OnDisk::writeToArticle(Article& art, string& path) {
	string art_path = "db/";
	art_path += path;
	art_path += "/";
	art_path += to_string(art.getId());
	ofstream file(art_path);
	file << art.getTitle() << endl << art.getAuthor() << endl << art.getText();
	file.close();
}
