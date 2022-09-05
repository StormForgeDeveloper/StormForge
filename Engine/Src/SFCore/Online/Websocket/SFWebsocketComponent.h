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

#pragma once

#include "SFTypedefs.h"

#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Task/SFTask.h"




namespace SF
{

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class WebsocketComponent
	//

    class WebsocketComponent : public LibraryComponent
    {
    public:

        using super = LibraryComponent;
        static constexpr StringCrc64 TYPE_NAME = "WebsocketComponent";

    public:

        WebsocketComponent();
        virtual ~WebsocketComponent();

        virtual const StringCrc64& GetTypeName() const override { return TYPE_NAME; }

        virtual Result InitializeComponent() override;
       
        static void WebsocketLog(int level, const char* line);
    };



}
