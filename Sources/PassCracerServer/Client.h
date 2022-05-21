#ifndef CLIENT_H
#define CLIENT_H
#include<asio.hpp>
#include "..\HeaderDirectory\Headers.h"
#include "ClientManager.h"

namespace CONCEPT
{
	template <typename TYPE>
	concept Message = std::is_base_of<BASE_HEADER, TYPE>::value;
}


class Client
{
protected:
	typedef asio::ip::tcp tcp;
	tcp::socket m_connection;
	uint64_t m_id;
	Client(tcp::socket&& socket) : m_connection(std::move(socket)), m_id(0)
	{}
public:
	bool operator==(const Client& c)
	{
		return c.m_id == m_id;
	}
};


class Owner : public Client
{
	
};

class Zombie : public Client
{

};

#endif