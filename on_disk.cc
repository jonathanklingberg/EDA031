#include "on_disk.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

OnDisk::OnDisk(){}

bool OnDisk::createNG(const string& news_group_name) {

}

bool OnDisk::removeNG(int news_group_id) {

}

vector<NewsGroup> OnDisk::listNGs() const {

}

vector<Article> OnDisk::listArticles(int news_group_id) const {

}

bool OnDisk::addArticle(int news_group_id, const string& art_title,
		const string& art_author, const string& art_text) {

}

bool OnDisk::removeArticle(int news_group_id, int article_id) {

}