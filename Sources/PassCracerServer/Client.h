#ifndef CLIENT_H
#define CLIENT_H
#include<asio.hpp>
#include "Headers.h"
#include "ClientManager.h"
enum class  CLIENT_TYPE : uint8_t
{
	OWNER = 0x0F0F,
	CLIENT = 0xF0F0,
};

enum class CONNECTION_TYPE : uint8_t
{
	PASSIVE = 0xFFFF,
	ACTIVE = 0x0000,
};

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
	CONNECTION_TYPE m_connType;
};

class Zombie : public Client
{

};

#endif