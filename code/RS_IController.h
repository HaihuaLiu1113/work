#ifndef RSIController_H
#define RSIController_H
#include <string>

class RSIController
{
public:
	RSIController(){}
	virtual ~RSIController(){}
	virtual void run() = 0;
};

#endif //RSIController_H