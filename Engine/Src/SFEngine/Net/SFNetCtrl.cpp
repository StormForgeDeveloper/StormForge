////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net message implementation
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Net/SFNetCtrl.h"



namespace SF {
namespace Net {

	tag_MsgNetCtrlBuffer GetNullMsgNetCtrlBuffer()
	{
		tag_MsgNetCtrlBuffer buffer;
		memset(&buffer,0,sizeof(buffer));
		return buffer;
	}

} // namespace Net
} // namespace SF


