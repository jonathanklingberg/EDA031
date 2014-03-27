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
	
	//Test NewsGroup
}