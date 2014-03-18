class Message_handler {

public:
	Message_handler(connection conn) : conn(conn) {};
	void read();
	void list_NGs();
    void create_NG();
    void list_art();
    void create_art();
    void delete_art();
    void get_art();
    
private:
	Connection conn;
	
	};
