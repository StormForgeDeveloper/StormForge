////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : HTTP client
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Online/HTTP/SFHTTPClient.h"
#include "Online/HTTP/SFHTTPClientSystem.h"
#include "Util/SFTrace.h"
#include "ResultCode/SFResultCodeLibrary.h"

namespace SF
{
    
    HTTPClient::HTTPClient()
    {
    }

    HTTPClient::~HTTPClient()
    {
    }

    void HTTPClient::SetURL(const String& url)
    {
        m_URL = url;
    }




}
