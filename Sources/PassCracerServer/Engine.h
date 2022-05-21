#ifndef ENGINE_H
#define ENGINE_H
class AbstractEngine
{
protected:
	AbstractEngine() {}
public:
	virtual  operator()(void) process() = 0;
};

class RangeEngine
{
	size_t m_pos;
public:
	operator()(void) process()
	{

	}
	size_t getPos() { return m_pos; }
};
#endif 