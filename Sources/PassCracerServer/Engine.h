#ifndef ENGINE_H
#define ENGINE_H
class AbstractEngine
{
protected:
	AbstractEngine() {}
public:
	virtual  void process() = 0;
};

class SimpleEngine
{
public:
	virtual void process()
	{

	}
};



#endif 