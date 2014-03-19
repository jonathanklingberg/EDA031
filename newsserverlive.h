
#include "newsserverinterface.h"
#include <string>
#include <vector>

using namespace std;

class Newsserverlive : public Newsserverinterface {
    
    public:
    
    Newsserverlive();
    ~Newsserverlive();
    
    virtual vector<> get_newsgroups(int group_id) const;
    virtual void create_newsgroup(string name);
    virtual void delete_newsgroup(int group_id);
    virtual vector<> list_articles(int group_id) const;
    virtual vector<> get_article(int group_id,int article_id) const;
    virtual void create_article(int group_id,string title,string author,string text);
    virtual void delete_article(int group_id,int article_id);
    
    private:
    

    
    
    
};