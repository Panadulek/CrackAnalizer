#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H
#include<atomic>
#include<list>
#include "Client.h"
class ClientManager
{
	std::list<Client*> m_clients;
	std::atomic<bool> m_mutex;
	Owner* m_owner;
public:
	void setOwner(Owner* owner)
	{
		m_owner = owner;
	}
	void addClient(Client* c)
	{
		m_mutex.wait(false);
		m_clients.push_back(c);
		m_mutex.notify_all();
	}
	void removeClient(Client* c)
	{
		m_mutex.wait(false);
		m_clients.remove(c);
		m_mutex.notify_all();
	}
	size_t getClientsCounter()
	{
		m_mutex.wait(false);
		size_t size = m_clients.size();
		m_mutex.notify_all();
		return size;
	}
	template<CONCEPT::Engine EngineType>
	void process(const EngineType &engine)
	{

	}
};

#endif