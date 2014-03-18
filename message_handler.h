class Message_handler {

public:
	Message_handler(connection conn) : conn(conn) {};
	void read();
	
    
private:
	Connection conn;
	
	};
