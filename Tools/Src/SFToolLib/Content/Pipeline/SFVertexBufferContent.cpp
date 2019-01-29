////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : VertexBuffer base
//
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UMVertexBufferContent.h"




////////////////////////////////////////////////////////////////////////////////////////////////
//
// UMVertexBufferContent::Channel
//

UMVertexBufferContent::BlendingInfoSFation::BlendingInfoSFation()
{
	memset(this, 0, sizeof(BlendingInfoSFation));
}

void UMVertexBufferContent::BlendingInfoSFation::AddBlend( int blendIndex, float blendWeight )
{
	if( blendIndex < 0 || blendWeight <= 0 ) // we don't need to add
		return;

	for( int iData = 0; iData < UMVertexBufferContent::MAX_BONEPERVERTEX; iData++ )
	{
		// replace if index is already exists
		if( BlendIndices[iData] == blendIndex )
		{
			BlendWeights[iData] = blendWeight;
			BlendIndices[iData] = blendIndex;
			return;
		}
	}

	for( int iData = 0; iData < UMVertexBufferContent::MAX_BONEPERVERTEX; iData++ )
	{
		// drop anything smaller wegiht than new weight
		if( BlendWeights[iData] < blendWeight )
		{
			BlendWeights[iData] = blendWeight;
			BlendIndices[iData] = blendIndex;
			return;
		}
	}
}

void UMVertexBufferContent::BlendingInfoSFation::NoSFalizeWeights()
{
	double sum = 0;
	for( int iData = 0; iData < UMVertexBufferContent::MAX_BONEPERVERTEX; iData++ )
	{
		sum += BlendWeights[iData];
	}

	if( sum <= std::numeric_limits<float>::epsilon() )
		return; // we can't noSFalize this

	double invSum = 1.0 / sum;

	for( int iData = 0; iData < UMVertexBufferContent::MAX_BONEPERVERTEX; iData++ )
	{
		BlendWeights[iData] = (float)(invSum * BlendWeights[iData]);
	}
}




////////////////////////////////////////////////////////////////////////////////////////////////
//
// UMVertexBufferContent::Channel
//

// channel
UMVertexBufferContent::Channel::Channel(UINT numVertex, StreamDataType streamType, StreamChannelType channelType, UINT numElement)
	:NumberOfVertex(0)
	,StreamType(streamType)
	,ChannelType(channelType)
	,NumElement(numElement)
	,pStreamData(nullptr)
{
	SetNumberOfVertex(numVertex);
}

UMVertexBufferContent::Channel::~Channel()
{
	if( pStreamData )
		delete pStreamData;
}

// allocate stream data buffer
UINT UMVertexBufferContent::Channel::GetBufferSize() const
{
	UINT stride = GetStride();
	UINT dataSize = stride * NumberOfVertex;
	return dataSize;
}

// Stride
UINT UMVertexBufferContent::Channel::GetStride() const
{
	UINT elementSize = 0;
	switch( StreamType )
	{
	case StreamDataType::BYTE:
		elementSize = sizeof(BYTE);
		break;
	case StreamDataType::FLOAT:
		elementSize = sizeof(FLOAT);
		break;
	}

	UINT stride = elementSize * NumElement;
	return stride;
}

// allocate stream data buffer
bool UMVertexBufferContent::Channel::SetNumberOfVertex( UINT numberOfVertex )
{
	if( NumberOfVertex == numberOfVertex )
		return true;

	UINT oldDataSize = GetBufferSize();

	NumberOfVertex = numberOfVertex;

	UINT dataSize = GetBufferSize();

	// we don't have to allocate new buffer
	if( dataSize <= oldDataSize )
		return true;

	if( pStreamData != nullptr )
		delete pStreamData;

	pStreamData = new BYTE[dataSize];

	return true;
}



//////////////////////////////////////////////////////////////////////////////////////////////
//
//	class UMVertexBufferContent
//

UMVertexBufferContent::UMVertexBufferContent()
	:m_NumberOfVertex(0)
{
}

UMVertexBufferContent::~UMVertexBufferContent()
{
	std::for_each( m_Channels.begin(), m_Channels.end(), []( Channel* pChannel )
	{
		delete pChannel;
	});

	m_Channels.clear();
}

// Get stride
UINT UMVertexBufferContent::GetStride()
{
	UINT stride = 0;
	std::for_each( m_Channels.begin(), m_Channels.end(), [&]( Channel* pChannel )
	{
		stride += pChannel->GetStride();
	});

	return stride;
}

// Get number of vertex
UINT UMVertexBufferContent::GetNumberOfVertex()
{
	return m_NumberOfVertex;
}

// Set number of vertex
void UMVertexBufferContent::SetNumberOfVertex( UINT numVertex )
{
	if( m_NumberOfVertex == numVertex )
		return;

	m_NumberOfVertex = numVertex;

	std::for_each( m_Channels.begin(), m_Channels.end(), [&]( Channel* pChannel )
	{
		pChannel->SetNumberOfVertex(m_NumberOfVertex);
	});
}

// Get vertex channel by index
UMVertexBufferContent::Channel* UMVertexBufferContent::GetVertexChannel(UINT iChannel)
{
	if( m_Channels.size() <= iChannel )
	{
		assert(!"Out of bounds");
		return nullptr;
	}

	return m_Channels[iChannel];
}

// Get specific channel by type
UMVertexBufferContent::Channel* UMVertexBufferContent::GetVertexChannel(StreamChannelType channelType, UINT index)
{
	Channel *pFoundChannel = nullptr;

	std::for_each( m_Channels.begin(), m_Channels.end(), [&]( Channel* pChannel )
	{
		if( channelType == pChannel->ChannelType )
		{
			if( index == 0 )
			{
				pFoundChannel = pChannel;
			}
			index--;
		}
	});

	return pFoundChannel;
}

// Add vertex channel
UMVertexBufferContent::Channel* UMVertexBufferContent::AddVertexChannel(StreamDataType streamType, StreamChannelType channelType, UINT numElement)
{
	Channel* pNewChannel = new Channel(m_NumberOfVertex, streamType, channelType, numElement);
	m_Channels.push_back(pNewChannel);
	return pNewChannel;
}

