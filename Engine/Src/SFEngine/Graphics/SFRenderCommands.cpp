////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Render command
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Graphics/SFRenderCommands.h"
#include "Graphics/SFGraphicDevice.h"


namespace SF
{

	void RenderCommand_KickFrame::RunCommand(GraphicDevice* pGraphicDevice)
	{
		if (pGraphicDevice->BeginFrame())
		{
			pGraphicDevice->RenderFrame();
			pGraphicDevice->EndFrame();
		}
	}


}

