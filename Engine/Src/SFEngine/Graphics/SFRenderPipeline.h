////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Render Pipeline
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Object/SFObject.h"
#include "Container/SFSortedArray.h"


namespace SF
{

	class GraphicDevice;
	class RenderPipelineStage;


	////////////////////////////////////////////////////////////////////
	//
	//	Render Pipeline
	//

	class RenderPipeline
	{
	public:

		typedef SortedArray<int32_t, RenderPipelineStage*, false> StageArray;
		typedef StageArray::Iterator Iterator;

	private:

		IHeap& m_Heap;

		StageArray m_Stages;

	public:
		RenderPipeline(IHeap& heap);
		virtual ~RenderPipeline();


		IHeap& GetHeap() { return m_Heap; }


		// Pipeline iterator
		Iterator begin() { return m_Stages.begin(); }
		Iterator end() { return m_Stages.end(); }
	};



}

