////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 StormForge
// 
// Author : KyungKun Ko
//
// Description : Spherical shell matching
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Thread/SFSystemSynchronization.h"
#include "Container/SFStaticDoubleLinkedList.h"
#include "Container/SFDualSortedMap.h"
#include "Container/SFArray.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"
#include "Util/SFRandom.h"
#include "Math/SF3DMath.h"




namespace SF
{

	//////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	UserPreference class
	//

	class UserPreference
	{
	public:
		// preference dimension, let's assume we can factorize user preference into 8 factors(-1.0 ~ 1.0).
		static constexpr int MAX_PREFERENCE_DIMENSION = 8;
		// Maximum length, We will use 4.5 that little higher then actual value. sqrt(MAX_PREFERENCE_DIMENSION) = 2.828
		static constexpr float MAX_PREFERENCE_LENGTH = 2.9f;

		union {
			Vector4 PackedFactors[MAX_PREFERENCE_DIMENSION/4];
			float PreferenceFactors[MAX_PREFERENCE_DIMENSION];
		};

	private:
		// preference length and square length
		float m_preferenceLength = 0, m_preferenceSqLength = 0;
		uint m_directionID = 0;

	public:
		// constructor
		UserPreference()
		{
			memset(PreferenceFactors, 0, sizeof(PreferenceFactors));
		}

		UserPreference(const UserPreference& src)
		{
			memcpy(PreferenceFactors, src.PreferenceFactors, sizeof(PreferenceFactors));
			m_preferenceSqLength = src.m_preferenceSqLength;
			m_preferenceLength = src.m_preferenceLength;
			m_directionID = src.m_directionID;
		}

		// Get length
		float GetLength() const { return m_preferenceLength; }
		float GetSquareLength() const { return m_preferenceSqLength; }

		// Update length
		void OnFactorUpdated()
		{
			m_preferenceSqLength = Dot(*this);
			m_preferenceLength = sqrt(m_preferenceSqLength);

			uint dirID = 0;
			for (int i = 0; i < MAX_PREFERENCE_DIMENSION; i++)
			{
				if(PreferenceFactors[i] >= 0)
					dirID |= (1 << i);
			}
			m_directionID = dirID;
		}

		// Get direction ID
		uint GetCellDirectionID() const { return m_directionID; }

		// Dot product
		float Dot(const UserPreference& op2) const
		{
			float dist = 0.0f;


			for (int iPack = 0; iPack < countof(PackedFactors); iPack++)
			{
				dist += PackedFactors[iPack].Dot4(op2.PackedFactors[iPack]);
			}

			//for (int i = 0; i < MAX_PREFERENCE_DIMENSION; i++)
			//	dist += PreferenceFactors[i] * op2.PreferenceFactors[i];

			return dist;
		}

		// Distance of two vector
		float Dist(const UserPreference& op2) const
		{
			float dist = 0.0f;

			for (int iPack = 0; iPack < countof(PackedFactors); iPack++)
			{
				auto diff = PackedFactors[iPack] - op2.PackedFactors[iPack];
				dist += diff.Dot4(diff);
			}

#if 0 //defined(_DEBUG)
			float distS = 0.0f;
			for (int i = 0; i < MAX_PREFERENCE_DIMENSION; i++)
				distS += pow(PreferenceFactors[i] - op2.PreferenceFactors[i], 2);
			Assert(abs(distS - dist) < 0.0001f);
#endif

			return sqrt(dist);
		}

		// initialize with random value
		void InitRandom()
		{
			for (int iPack = 0; iPack < countof(PackedFactors); iPack++)
			{
				PackedFactors[iPack] = Vector4(Util::Random.RandF(), Util::Random.RandF(), Util::Random.RandF(), Util::Random.RandF());
			}
			//for (int i = 0; i < countof(PreferenceFactors); i++)
			//	PreferenceFactors[i] = (float)Util::Random.RandF();
			OnFactorUpdated();
		}

		// copy operator
		UserPreference& operator =(const UserPreference& src)
		{
			memcpy(PreferenceFactors, src.PreferenceFactors, sizeof(PreferenceFactors));
			m_preferenceSqLength = src.m_preferenceSqLength;
			m_preferenceLength = src.m_preferenceLength;
			m_directionID = src.m_directionID;
			return *this;
		}
	};




	/////////////////////////////////////////////////////////////////////
	//
	//	PreferencePlayer for matchmaking system
	//

	class PreferencePlayer
    {
	public:


    public:

		// Constructor
        PreferencePlayer();

		// Constructor with initialize
		PreferencePlayer(uint playerID, const UserPreference& preference);
        ~PreferencePlayer();

		// Initialize player
		void Initialize(uint playerID, const UserPreference& preference)
		{
			m_PlayerID = playerID;
			m_Preference = preference;
		}

		// Set new preference vector
		void SetPreference(const UserPreference& preference)
		{
			m_Preference = preference;
		}

		// User preference
		const UserPreference& GetPreference() const { return m_Preference; }

		// Get currently assigned shell id
		uint GetCurrentShellID() const { return m_CurrentShellID; }

		// set current shell id
		bool SetCurrentShellID(uint shellID);

		// Get listnode
		StaticDoubleLinkedList::Node& GetListNode() { return m_ListNode; }

		// Get player id
		uint GetPlayerID() const { return m_PlayerID; }


		// helper util
		static PreferencePlayer* ToPlayerPtr(StaticDoubleLinkedList::Node* nodePtr)
		{
			return reinterpret_cast<PreferencePlayer*>(((intptr_t)nodePtr - offsetof(PreferencePlayer, m_ListNode)));
		}


	public:

		// Is available
		bool m_isAvailable; 

	private:
		// PreferencePlayer ID
		uint m_PlayerID;

		// preference vector
		UserPreference m_Preference;

		// Listnode
		StaticDoubleLinkedList::Node m_ListNode;

		// current Shell Index, if belong to a Shell
		uint m_CurrentShellID = -1;
    };

	//typedef SharedPointerAtomicT<PreferencePlayer> PlayerPtr;


	//////////////////////////////////////////////////////////////////////////////////
	//
	//	SphericalShellManager class
	//

	class SphericalShell
	{
	public:

		static constexpr uint InvalidShellID = -1;

		struct SearchContext
		{
			uint PlayerID = 0;
			UserPreference Preference;
			uint MaxPlayerToSearch = 0;
			float fMaxDist = 0;
			//SortedArray<float,PreferencePlayer*, false> SearchResult;
			Array<PreferencePlayer*>& SearchResult;

			SearchContext(Array<PreferencePlayer*>& result)
				: SearchResult(result)
			{
			}
		};

		typedef StaticDoubleLinkedList PlayerListType;

		struct Cell
		{
			CriticalSection PlayerListLock;
			PlayerListType PlayerList;
		};


	public:

		// Constructor
		SphericalShell(IHeap& heap, uint shellID, uint preferenceDimension);
		~SphericalShell();

		// Get method for shell ID
		uint GetShellID() const { return m_ShellID; }

		// Add a player. If the player is in the shell already  you need to 
		Result AddPlayer(PreferencePlayer *pPlayer);

		// Remove a player
		Result RemovePlayer(PreferencePlayer *pPlayer);

		// Remove a player
		//void RemovePlayer(PreferencePlayer *pPlayer);

		void SearchForMatch(SearchContext& searchContext);


	private:

		// Shell ID
		uint m_ShellID;

		// Lock for player list
		CriticalSection m_PlayerListLock;

		// player list
		DynamicArray<Cell*> m_DirectionalCells;
	};




	//////////////////////////////////////////////////////////////////////////////////
	//
	//	SphericalShellManager class
	//

	class SphericalShellManager
	{
	public:

		// Search threshold when searching, if all results exceed this distance, search will end
		static constexpr float SEARCH_THRESOLD = (0.05f);



	private:

	public:

		// Constructor
		SphericalShellManager(IHeap& heap);
		virtual ~SphericalShellManager();

		// Get heap
		IHeap& GetHeap() { return m_Heap; }

		// initialize
		Result Initialize(uint numberOfShell);

		// Clear
		void Clear();

		// find shell ID for player
		uint CalculateShellForPlayer(PreferencePlayer* pPlayer);

		// Add player
		Result AddPlayer(PreferencePlayer* pNewPlayer );

		// Remove player
		Result RemovePlayer(PreferencePlayer* pPlayer);

		// Update shell player
		Result UpdatePlayerShell(PreferencePlayer* pPlayer);

		// Get number of player
		size_t GetPlayerCount() const { return (size_t)m_PlayerCount.load(std::memory_order_relaxed); }


		// Matching 
		Result MatchMake(PreferencePlayer* pPlayer, Array<PreferencePlayer*> &players);


	private:

		// Heap
		Heap m_Heap;

		//
		float m_ShellThickness = 0;

		// Array of player maps
		DynamicArray<SphericalShell*>	m_Shells;

		std::atomic<int64_t> m_PlayerCount;
	};



}; // namespace SF

