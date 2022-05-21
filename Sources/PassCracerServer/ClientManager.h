#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H
#include<atomic>
#include<list>
#include "Client.h"
class ClientManager
{
	std::list<const Client*> m_queue;
	Client m_manager;
	std::atomic<bool> m_mutex;

public:
	ClientManager() : m_mutex(true) {}
	void addClient(const Client* client)
	{
		m_mutex.wait(true);
		m_queue.push_back(client);
		m_mutex.notify_all();
	}
	void removeClient(const Client* client)
	{
		m_mutex.wait(true);
		unsigned ret = m_queue.remove(client);
		m_mutex.notify_all();
	}
	template<CONCEPT::Message TYPE>
	void send(const char* message, size_t size);
};

#endif