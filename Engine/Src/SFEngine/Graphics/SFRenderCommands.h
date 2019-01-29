////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Render commands
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Object/SFObject.h"
#include "Graphics/SFRenderCommand.h"

namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	Render commands
	//

	class RenderCommand_KickFrame : public RenderCommand
	{
	private:

	public:
		RenderCommand_KickFrame(const CallTrack& callTrack) : RenderCommand(callTrack) {}

		virtual void RunCommand(GraphicDevice* pGraphicDevice) override;
	};




}

