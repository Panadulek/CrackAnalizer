#ifndef HEADERS_H
#define HEADERS_H
#include <cstdint>

#define CONST_EXPR_SIZE(X) size_t get##X##Size() \
							{\
								constexpr size_t size = sizeof(X); return size;\
							}

class BASE_HEADER
{
protected:
	enum class TYPE_HEADER : uint8_t
	{
		STATISTIC,
		QUEST,
		CHANGE_CONNECTION,
		FINISHED_TASK,
	};
	TYPE_HEADER m_type;
	struct StructBaseHeader
	{
		TYPE_HEADER type;
	};
	BASE_HEADER(TYPE_HEADER type) : m_type(type) {}
public:
	typedef StructBaseHeader BaseHeader;
	BaseHeader getBaseHeader()
	{
		BaseHeader header = { .type = m_type };
		return header;
	}
	CONST_EXPR_SIZE(BaseHeader)
};
class STATISTIC_HEADER : public BASE_HEADER
{
public:
	enum class STYPE : uint8_t
	{
		GHZ,
		EXECUTE_TIME,
		THREAD_COUNTER,
		AMOUNT_OF_ZOMBIES,
	};
private:
	
	uint64_t m_data;
	STYPE m_type;
	struct StructStatisticHeader
	{
		uint64_t executeTime;
		STYPE type;
	};
public:
	typedef StructStatisticHeader StatisticHeader;
	STATISTIC_HEADER(uint64_t executeTime) : BASE_HEADER(TYPE_HEADER::STATISTIC), m_executeTime(executeTime) {}
	StatisticHeader getStatHeader()
	{
		StatisticHeader header = { .executeTime = m_executeTime };
		return header;
	}
	CONST_EXPR_SIZE(StatisticHeader)
};

class QUEST_HEADER : public BASE_HEADER
{
public:
	enum class ORDER : uint8_t
	{
		//C - crypted P-preapered e -enCrypted
		CPE,
		CEP,
		PCE,
		PEC,
		ECP,
		EPC,
	};
private:
	uint64_t m_cryptedStringSize;
	uint64_t m_preaperedStringSize;
	uint64_t m_enCryptedStringSize;
	ORDER m_order;
	struct StructQuestHeader
	{
		uint64_t cryptedStringSize;
		uint64_t preaperedStringSize;
		uint64_t enCryptedStringSize;
		ORDER order;
	};
public:
	typedef StructQuestHeader QuestHeader;
	QUEST_HEADER(uint64_t cSize, uint64_t pSize, uint64_t eSize, ORDER order) : m_cryptedStringSize(cSize), m_preaperedStringSize(pSize), 
		m_enCryptedStringSize(eSize), m_order(order), BASE_HEADER(TYPE_HEADER::QUEST) {}
	QuestHeader getQHeader()
	{
		QuestHeader header = {
			.cryptedStringSize = m_cryptedStringSize,
			.preaperedStringSize = m_preaperedStringSize,
			.enCryptedStringSize = m_enCryptedStringSize,
			.order = m_order
		};
		return header;
	}
	CONST_EXPR_SIZE(QuestHeader)
};

class CHANGE_CONNECTION_HEADER : public BASE_HEADER
{
public:
	enum class CONNECTION_TYPE : uint8_t
	{
		ACTIVE,
		PASSIV,
	};
private:
	CONNECTION_TYPE m_cType;
	struct StructChangeConnectionHeader
	{
		CONNECTION_TYPE cType;
	};
public:
	typedef StructChangeConnectionHeader ChangeConnectionHeader;
	CHANGE_CONNECTION_HEADER(CONNECTION_TYPE ctype) : m_cType(ctype), BASE_HEADER(TYPE_HEADER::CHANGE_CONNECTION) {}
	CONST_EXPR_SIZE(ChangeConnectionHeader)
};

class FINISHED_TASK_HEADER : public BASE_HEADER
{
	uint8_t m_result;
public:
	FINISHED_TASK_HEADER(bool result) :m_result(result), BASE_HEADER(TYPE_HEADER::FINISHED_TASK) {}
	bool getResult() { return m_result; }
};



#endif
