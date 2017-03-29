#ifndef RSMsgEndecoder_H
#define RSMsgEndecoder_H
#include <string>
class RSMsgEndecoder
{
public:
	RSMsgEndecoder();
	~RSMsgEndecoder();

	static std::string endecodeHeartbeatMsg();
	
};

#endif //RSMsgEndecoder_H