#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Network.hpp>
using namespace sf;
using namespace std;
int main()
{
	// Create a socket and connect it to 192.168.1.50 on port 55001
	sf::TcpSocket socket;
	IpAddress ipaddress;
	cout << IpAddress::LocalHost << endl;

	socket.connect(IpAddress::LocalHost,55001,Time::Zero);
	if (Socket::Status::Disconnected)
		cout << 1 << endl;
	if (Socket::Status::Done)
		cout << "Yeah babby" << endl;
	if (Socket::Status::Error)
		cout << 2 << endl;
	if (Socket::Status::NotReady)
		cout <<3 << endl;
	if (Socket::Status::Partial)
		cout << 5<< endl;
	cout << (IpAddress::Broadcast) << endl;
	cout << socket.AnyPort << endl;
	cout << ipaddress.getLocalAddress() << endl;
	cout<<ipaddress.getPublicAddress() << endl;
	cout<<socket.getLocalPort()<<" "<<socket.getRemoteAddress()<<socket.getRemotePort()<<endl;
	//socket.connect("192.168.0.101",50136);
	cout << socket.getLocalPort() << " " << socket.getRemoteAddress() << socket.getRemotePort() << endl;
	socket.disconnect();
	cout << "----------" << endl;
	sf::TcpListener listener;
	listener.listen(55001);
	listener.
	// Endless loop that waits for new connections
	while (true)
	{
		sf::TcpSocket client;
		if (listener.accept(client) == sf::Socket::Done)
		{
			// A new client just connected!
			std::cout << "New connection received from " << client.getRemoteAddress() << std::endl;
			break;
		}
	}
	/*socket.connect(socket.getRemoteAddress() , socket.getLocalPort());
	// Send a message to the connected host
	std::string message = "Hi, I am a client";
	cout << message << endl;
	socket.send(message.c_str(), message.size() + 1);
	// Receive an answer from the server
	char buffer[1024];
	std::size_t received = 0;
	socket.receive(buffer, sizeof(buffer), received);
	std::cout << "The server said: " << buffer << std::endl;
	system("pause");
	// ----- The server -----
	// Create a listener to wait for incoming connections on port 55001
	sf::TcpListener listener;
	listener.listen(socket.getLocalPort());
	// Wait for a connection
	sf::TcpSocket socket1;
	listener.accept(socket1);
	std::cout << "New client connected: " << socket1.getRemoteAddress() << std::endl;
	// Receive a message from the client
	char buffer1[1024];
	std::size_t received1 = 0;
	socket1.receive(buffer1, sizeof(buffer1), received1);
	std::cout << "The client said: " << buffer1 << std::endl;
	// Send an answer
	std::string message1 = "Welcome, client";
	socket1.send(message1.c_str(), message1.size() + 1);

	system("pause");*/
}