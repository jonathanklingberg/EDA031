class Message_handler {

public:
	Message_handler(connection conn) : conn(conn) {};
	void read();
	bool sendCommand(const string command);
	bool sendParam(const string param); 
	bool sendEnd(const sting end);
	
private:
	Connection conn;
	
	};
