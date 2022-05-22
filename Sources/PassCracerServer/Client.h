#ifndef CLIENT_H
#define CLIENT_H
#include<asio.hpp>
#include "..\HeaderDirectory\Headers.h"
#include "Engine.h"
namespace CONCEPT
{
	template <typename TYPE>
	concept Message = std::is_base_of<BASE_HEADER, TYPE>::value;
	template <typename TYPE>
	concept Engine = std::is_base_of<AbstractEngine, TYPE>::value;
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
	virtual void run() = 0;
};

class Zombie : public Client
{
public:
	Zombie(tcp::socket&& socket) : Client(std::move(socket))
	{}
	void run() override;
	template<CONCEPT::Message TYPE, typename ... ARGSPACK>
	bool send(TYPE type, ARGSPACK... args);
	template<CONCEPT::Message TYPE>
	auto read(TYPE type);
};
class ClientManager;
class Owner : public Client
{
	ClientManager* m_manager;
public:
	Owner(tcp::socket&& socket, ClientManager* manager) : Client(std::move(socket)), m_manager(manager)
	{
		m_manager->setOwner(this);
	}
	void run() override;
	template<CONCEPT::Message TYPE, typename ... ARGSPACK>
	bool send(TYPE type, ARGSPACK... args);
	template<CONCEPT::Message TYPE>
	auto read(TYPE type);
};


#endif