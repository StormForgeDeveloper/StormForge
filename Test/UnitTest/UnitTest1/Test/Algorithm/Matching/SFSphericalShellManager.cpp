////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 StormForge
// 
// Author : KyungKun Ko
//
// Description : Spherical shell matching
//
////////////////////////////////////////////////////////////////////////////////



#include "UnitTest1PCH.h"

#include "SFSphericalShellManager.h"


namespace SF
{

	///////////////////////////////////////////////////////////////////////////////
	//
	//	Match maker player implementation
	//

	constexpr int UserPreference::MAX_PREFERENCE_DIMENSION;
	constexpr float UserPreference::MAX_PREFERENCE_LENGTH;


	///////////////////////////////////////////////////////////////////////////////
	//
	//	Match maker player implementation
	//

	PreferencePlayer::PreferencePlayer()
	{
	}

	PreferencePlayer::PreferencePlayer( uint playerID, const UserPreference& preference)
		: m_PlayerID(playerID)
	{
		SetPreference( preference );
	}

	PreferencePlayer::~PreferencePlayer()
	{
	}

	bool PreferencePlayer::SetCurrentShellID(uint shellID)
	{
		auto curShell = m_CurrentShellID;
		if (curShell == shellID)
			return true;

		if (shellID != SphericalShell::InvalidShellID
			&& curShell != SphericalShell::InvalidShellID)
		{
			Assert(false);// The player already has a shell id assigned
			return false;
		}

		m_CurrentShellID = shellID;
		return true;
	}



	//////////////////////////////////////////////////////////////////////////////////
	//
	//	SphericalShellManager class
	//

	constexpr uint SphericalShell::InvalidShellID;


	// Constructor
	SphericalShell::SphericalShell(IHeap& heap, uint shellID, uint preferenceDimension)
		: m_ShellID(shellID)
		, m_DirectionalCells(heap)
	{
		uint numCell = 1 << preferenceDimension;
		m_DirectionalCells.reserve(numCell);
		for (uint iCell = 0; iCell < numCell; iCell++)
		{
			m_DirectionalCells.push_back(new(heap) Cell);
		}
	}

	SphericalShell::~SphericalShell()
	{
		Cell* pCell = m_DirectionalCells.pop_back();
		for (; pCell; pCell = m_DirectionalCells.pop_back())
		{
			IHeap::Delete(pCell);
		}
		m_DirectionalCells.Clear();
	}

	// Add a player. If the player is in the shell already  you need to 
	Result SphericalShell::AddPlayer(PreferencePlayer *pPlayer)
	{
		if (pPlayer->GetCurrentShellID() != SphericalShell::InvalidShellID)
			return ResultCode::INVALID_STATE;

		Result result;

		uint cellDirID = pPlayer->GetPreference().GetCellDirectionID();
		auto cell = m_DirectionalCells[cellDirID];
		{
			//MutexScopeLock lock(m_PlayerListLock);
			MutexScopeLock lock(cell->PlayerListLock);
			result = cell->PlayerList.push_back(&pPlayer->GetListNode());
			if (!result)
				return result;
		}

		result = pPlayer->SetCurrentShellID(GetShellID());

		return result;
	}

	// Remove a player
	Result SphericalShell::RemovePlayer(PreferencePlayer *pPlayer)
	{
		if (pPlayer->GetCurrentShellID() != GetShellID())
			return ResultCode::INVALID_STATE;

		Result result;
		uint cellDirID = pPlayer->GetPreference().GetCellDirectionID();
		auto cell = m_DirectionalCells[cellDirID];

		{
			//MutexScopeLock lock(m_PlayerListLock);
			MutexScopeLock lock(cell->PlayerListLock);
			result = cell->PlayerList.Remove(&pPlayer->GetListNode());
			if (!result)
				return result;
		}

		result = pPlayer->SetCurrentShellID(SphericalShell::InvalidShellID);

		return result;
	}



	void SphericalShell::SearchForMatch(SearchContext& searchContext)
	{
		uint cellDirID = searchContext.Preference.GetCellDirectionID();
		auto& cell = *m_DirectionalCells[cellDirID];

		MutexScopeLock lock(cell.PlayerListLock);
		auto itemCount = cell.PlayerList.size();
		for(int iItem = 0; iItem < itemCount; iItem++)
		{
			StaticDoubleLinkedList::Node *pNode = cell.PlayerList.pop_front();
			if (pNode == nullptr)
				return;

			auto pPlayer = PreferencePlayer::ToPlayerPtr(pNode);

			// it's just pop
			pPlayer->SetCurrentShellID(InvalidShellID);

			if (pPlayer->GetPlayerID() == searchContext.PlayerID)
			{
				continue;
			}

			auto fCurDistance = searchContext.Preference.Dist(pPlayer->GetPreference());
			if (fCurDistance >= searchContext.fMaxDist)
			{
				if (searchContext.SearchResult.size() > searchContext.MaxPlayerToSearch)
				{
					// we don't have to add useless case
					cell.PlayerList.push_back(pNode);
					continue;
				}
				else
				{
					searchContext.fMaxDist = fCurDistance;
				}
			}
			else
			{
				// garbage collection
			}

			//searchContext.SearchResult.Insert(fCurDistance, pPlayer);
			searchContext.SearchResult.push_back(pPlayer);

			if (searchContext.SearchResult.size() >= (searchContext.MaxPlayerToSearch))
			{
				searchContext.SearchResult.resize(searchContext.MaxPlayerToSearch);
				return;
			}
		}

	}






	/////////////////////////////////////////////////////////////////////////////////////
	//
	//	SphericalShellManager
	//

	// Constructor
	SphericalShellManager::SphericalShellManager(IHeap& heap)
		: m_Heap("SphericalShellManager", heap)
		, m_Shells(m_Heap)
	{
	}

	SphericalShellManager::~SphericalShellManager()
	{
		Clear();
	}


	// initialize
	Result SphericalShellManager::Initialize(uint numberOfShell)
	{
		Result result;

		Clear();

		for (uint iShell = 0; iShell < numberOfShell; iShell++)
		{
			m_Shells.push_back(new(GetHeap()) SphericalShell(GetHeap(), iShell + 1, UserPreference::MAX_PREFERENCE_DIMENSION));
		}

		m_ShellThickness = UserPreference::MAX_PREFERENCE_LENGTH / (float)m_Shells.size();

		return result;
	}

	// Clear
	void SphericalShellManager::Clear()
	{
		for (auto itShell : m_Shells)
		{
			IHeap::Delete(itShell);
		}

		m_Shells.Clear();
	}

	// find shell ID for player
	uint SphericalShellManager::CalculateShellForPlayer(PreferencePlayer* pPlayer)
	{
		if (m_Shells.size() == 0)
			return 0;

		float fPreferenceLenPerPartitionInv = (1.f / (m_ShellThickness));
		return (uint)(pPlayer->GetPreference().GetLength() * fPreferenceLenPerPartitionInv);
	}




	// Add player
	Result SphericalShellManager::AddPlayer(PreferencePlayer* pNewPlayer)
	{
		if (pNewPlayer == nullptr)
			return ResultCode::INVALID_ARG;

		if (m_Shells.size() == 0)
			return ResultCode::FAIL;

		m_PlayerCount.fetch_add(1, std::memory_order_relaxed);

		auto shellID = CalculateShellForPlayer(pNewPlayer);
		return m_Shells[shellID]->AddPlayer(pNewPlayer);
	}


	// Remove player
	Result SphericalShellManager::RemovePlayer(PreferencePlayer* pPlayer)
	{
		if (m_Shells.size() == 0)
			return ResultCode::FAIL;

		auto shellID = pPlayer->GetCurrentShellID();
		if (shellID > m_Shells.size())
			return ResultCode::FAIL;

		m_PlayerCount.fetch_sub(1, std::memory_order_relaxed);
		
		return m_Shells[shellID]->RemovePlayer(pPlayer);
	}


	// Update shell player
	Result SphericalShellManager::UpdatePlayerShell(PreferencePlayer* pPlayer)
	{
		if (pPlayer == nullptr)
			return ResultCode::INVALID_ARG;

		if (m_Shells.size() == 0)
			return ResultCode::FAIL;

		MutexScopeLock lock(pPlayer->GetShellLock());

		auto shellID = pPlayer->GetCurrentShellID();
		auto newShellID = CalculateShellForPlayer(pPlayer);

		if (shellID == newShellID)
			return ResultCode::SUCCESS;

		if (shellID < m_Shells.size())
			m_Shells[shellID]->RemovePlayer(pPlayer);

		if (newShellID < m_Shells.size())
			m_Shells[newShellID]->AddPlayer(pPlayer);

		return ResultCode::SUCCESS;
	}



	Result SphericalShellManager::MatchMake(PreferencePlayer* pPlayer, Array<PreferencePlayer*> &players)
	{
		if (pPlayer == nullptr)
			return ResultCode::INVALID_POINTER;

		SphericalShell::SearchContext searchContext(players);
		searchContext.fMaxDist = 0;
		searchContext.MaxPlayerToSearch = (uint)players.GetAllocatedSize();

		int currentShell = -1;

		// if not assigned or not available
		//if( pPlayer->m_currentShell < 0 || pPlayer->m_isAvailable == false )
		//	return false;

		currentShell = pPlayer->GetCurrentShellID();
		if (currentShell == SphericalShell::InvalidShellID)
			currentShell = CalculateShellForPlayer(pPlayer);

		searchContext.PlayerID = pPlayer->GetPlayerID();
		searchContext.Preference = pPlayer->GetPreference();
		//searchContext.SearchResult.reserve(searchContext.MaxPlayerToSearch + 1);


		// searching Shells until get reasonable result
		int iChecked = 1;
		float fMaxDist = 0;

		m_Shells[currentShell]->SearchForMatch(searchContext);

		for (int iShell = 1; iChecked > 0 && searchContext.SearchResult.size() < searchContext.MaxPlayerToSearch; iShell++)
		{
			iChecked = 0;
			// checking lower Shell
			int iShellToCheck = currentShell - iShell;
			if (iShellToCheck >= 0)
			{
				iChecked++;

				m_Shells[iShellToCheck]->SearchForMatch(searchContext);
			}

			// checking upper Shell
			iShellToCheck = currentShell + iShell;
			if (iShellToCheck < m_Shells.size())
			{
				iChecked++;

				m_Shells[iShellToCheck]->SearchForMatch(searchContext);
			}

			// If we already has enough result then we don't have to further search outside radius
			float fDiffRadius = (float)(m_ShellThickness * iShell);
			if (searchContext.SearchResult.size() >= searchContext.MaxPlayerToSearch
				&& fDiffRadius > fMaxDist)
				break;

			if (iChecked == 0) // all Shell searched
				break;
		}

		// correct max result count
		auto numPlayerIds = searchContext.SearchResult.size();
		if (numPlayerIds > searchContext.MaxPlayerToSearch)
			numPlayerIds = searchContext.MaxPlayerToSearch;

		return ResultCode::SUCCESS;
	}



} // namespace SF


