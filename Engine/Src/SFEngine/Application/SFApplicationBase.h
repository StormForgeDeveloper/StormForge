////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Basic android application
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Container/SFCircularPageQueue.h"
#include "EngineObject/SFEngineObject.h"
#include "EngineObject/SFEngineTask.h"
#include "SFEngine.h"


namespace SF
{
	class Command;

	class ApplicationBase : public LibraryComponent
	{
	public:
	private:

		Heap m_Heap;

		CircularPageQueueAtomic<Command*> m_CommandQueue;

		bool m_IsPaused;

	private:


	public:

		ApplicationBase();
		~ApplicationBase();

		IHeap& GetHeap() { return *m_Heap.get(); }


		virtual Result InitializeComponent() override;
		virtual void DeinitializeComponent() override;



		virtual bool HandleKeyInput(int type, int action, int flags, int keyCode) { return false; }
		virtual bool HandleInput(int type, int motionAction, int flags, int buttonState, float x, float y) { return false; }


		bool IsPaused() { return m_IsPaused; }
		void SetPaused(bool paused) { m_IsPaused = paused; }



		template<class CommandType>
		CommandType* SendCommand()
		{
			auto pCommand = new(GetHeap()) CommandType(this);
			pCommand->Request();
			return pCommand;
		}

		template<class CommandType, class ...ArgTypes>
		CommandType* SendCommand(ArgTypes... args)
		{
			auto pCommand = new(GetHeap()) CommandType(this, args...);
			pCommand->Request();
			return pCommand;
		}

	};




	/////////////////////////////////////////////////////////////////
	//
	//	Command
	//

	class AppTask : public EngineTask
	{
	private:

	public:
		AppTask();
	};


	//class InputCommand : public Command
	//{
	//public:
	//	virtual void Run() override;
	//};
}

