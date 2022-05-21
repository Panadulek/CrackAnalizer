#include <asio.hpp>
#include <asio/ip/tcp.hpp>
#include <thread>
#include "Client.h"
typedef asio::ip::tcp tcp;

void work(tcp::socket&& socket)
{
	
}

int main()
{
	asio::io_context context;
	tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), 5555));
	while (true)
	{
		tcp::socket socket(context);
		acceptor.accept(socket);
		std::thread t(work, std::move(socket));
	}
	return 0;
}