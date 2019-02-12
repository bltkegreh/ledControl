#include <memory>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <regex>

#include "proxy.h"
#include "server.h"

int main()
{
	using namespace std;
	Proxy proxy(make_unique<ComplexLed>());
	
	const string serverFifo = "/tmp/server";
	const string clientFifo = "/tmp/client";

	const regex commandExpression("(\\d+)\\s+(.*)");

	Server server(serverFifo,clientFifo);
	server.init();
	while(1)
	{
		string readStr;
		server.readData(readStr);
		if (!readStr.empty()) {
			smatch match;
			if(regex_search(readStr, match, commandExpression)) {
				string pid = match[1];
				string command = match[2];

				cout << "PID is " << pid << " command is " << command << endl;
				string answer = proxy.processRequest(command);
				cout << "Answer is " << answer << endl;

				server.writeData(pid, answer);
			}
			else
			{
				cout << "bad request " << readStr << endl;
			}
		}
	}
}
