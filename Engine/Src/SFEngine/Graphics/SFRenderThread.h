////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Rendering thread
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Multithread/SFThread.h"


namespace SF
{
	class GraphicDevice;

	////////////////////////////////////////////////////////////////////
	//
	//	Render Thread
	//
	class RenderThread : public Thread
	{
	private:

		GraphicDevice* m_pDevice;



	public:
		RenderThread(GraphicDevice* pDevice);
		virtual ~RenderThread();

		virtual void Run() override;
	};




}

