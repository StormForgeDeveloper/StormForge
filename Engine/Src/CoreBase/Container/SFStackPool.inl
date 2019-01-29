////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread utilities Stack base object pool
//
////////////////////////////////////////////////////////////////////////////////



namespace SF {


		//
		//StackPool::Header::Header()
		//	:pHead(nullptr),
		//	TSeqID(0)
		//{
		//	AssertRel( ((int64_t)this & (BR_ALIGN_DOUBLE-1)) == 0 );
		//}


		// for_each functor
		// NOTE: This method isn't thread safe
		template< class Functor >
		void StackPool::for_each(Functor func)
		{
			Item *pItem = m_head.load(std::memory_order_relaxed);
			while (pItem)
			{
				Item* pNext = pItem->pNext;
				func(pItem);
				pItem = pNext;
			}
		}


}

