////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Websocket
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"

#include "Online/Websocket/SFWebsocketComponent.h"
#include "Util/SFStringFormat.h"
#include "Online/Websocket/SFWebsocket.h"



namespace SF
{



	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class WebsocketComponent
	//

	WebsocketComponent::WebsocketComponent()
		: LibraryComponent("WebsocketComponent")
	{
	}

	WebsocketComponent::~WebsocketComponent()
	{
	}

	void WebsocketComponent::WebsocketLog(int level, const char* line)
	{
		switch (level)
		{
			case LLL_ERR	:
				SFLog(Websocket, Error, "{0}", line);
				break;
			case LLL_WARN	:
				SFLog(Websocket, Warning, "{0}", line);
				break;
			case LLL_NOTICE	:
				SFLog(Websocket, Info, "Notice {0}", line);
				break;
			case LLL_INFO	:
				SFLog(Websocket, Info, "{0}", line);
				break;
			case LLL_DEBUG	:
				SFLog(Websocket, Debug, "{0}", line);
				break;
			case LLL_PARSER	:
				SFLog(Websocket, Info, "Parser {0}", line);
				break;
			case LLL_HEADER	:
				SFLog(Websocket, Debug, "Header {0}", line);
				break;
			case LLL_EXT	:
				SFLog(Websocket, Debug, "Ext {0}", line);
				break;
			case LLL_CLIENT	:
				SFLog(Websocket, Debug, "Client {0}", line);
				break;
			case LLL_LATENCY:
				SFLog(Websocket, Debug, "Latency {0}", line);
				break;
			case LLL_USER	:
				SFLog(Websocket, Debug, "User {0}", line);
				break;
			case LLL_THREAD	:
				SFLog(Websocket, Info, "Thread {0}", line);
				break;
			default:
				SFLog(Websocket, Info, "{0}", line);
				break;
		}
	}


	Result WebsocketComponent::InitializeComponent()
	{
		int logs = LLL_ERR | LLL_WARN | LLL_NOTICE
			/* for LLL_ verbosity above NOTICE to be built into lws,
			 * lws must have been configured and built with
			 * -DCMAKE_BUILD_TYPE=DEBUG instead of =RELEASE */
			 /* | LLL_PARSER */ /* | LLL_HEADER */
			 // | LLL_EXT  | LLL_LATENCY 
			 //| LLL_INFO | LLL_CLIENT
			 //| LLL_DEBUG
			 //| LLL_USER
			;

		lws_set_log_level(logs, &WebsocketComponent::WebsocketLog);

		return super::InitializeComponent();
	}

}

