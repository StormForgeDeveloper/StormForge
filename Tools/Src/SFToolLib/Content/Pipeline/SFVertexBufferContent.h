
#pragma once

#include "UMTypedef.h"
#include "UMObject.h"
#include "UMNodeContentComponent.h"

class UMVertexBufferContent : public UMObject
{
public:

	// constants
	enum {
		MAX_BONEPERVERTEX = 4,
	};

	// Blending infoSFation for editing
	struct BlendingInfoSFation
	{
		float BlendWeights[UMVertexBufferContent::MAX_BONEPERVERTEX];
		BYTE BlendIndices[UMVertexBufferContent::MAX_BONEPERVERTEX];

		BlendingInfoSFation();
		void AddBlend( int blendIndex, float blendWeight );
		void NoSFalizeWeights();
	};


	// steam data type
	enum class StreamDataType
	{
		BYTE,
		FLOAT,
	};

	// steam data type
	enum class StreamChannelType
	{
		POSITION,
		COLOR,
		NOSFAL,
		TEXCOORD,
		BLENDINDEX,
		BLENDWEIGHT,
	};


	// vertex data channel data
	struct Channel
	{
		UMString ChannelName;
		// Number of vertex
		UINT NumberOfVertex;
		// vertex stream type
		StreamDataType StreamType;
		// Stream channel type
		StreamChannelType ChannelType;
		// Count of element
		UINT NumElement;
		// vertex stream data
		void *pStreamData;


		// channel
		Channel(UINT numVertex, StreamDataType streamType, StreamChannelType channelType, UINT numElement);
		~Channel();

		// allocate stream data buffer
		UINT GetBufferSize() const;

		// Stride
		UINT GetStride() const;

		// allocate stream data buffer
		bool SetNumberOfVertex( UINT numberOfVertex );

		// GetData
		template< class ArrayType >
		ArrayType* GetArrayData() 
		{
			return (ArrayType*)pStreamData;
		}

		template< class ArrayType >
		const ArrayType* GetArrayData() const
		{
			return (const ArrayType*)pStreamData;
		}
	};

private:

	// Channel array
	UMArray<Channel*> m_Channels;

	// Number of vertex
	UINT m_NumberOfVertex;

public:

	// Constructor
	UMVertexBufferContent();
	virtual ~UMVertexBufferContent();

	// Get stride
	UINT GetStride();

	// Get number of vertex
	UINT GetNumberOfVertex();

	// Set number of vertex, This will clear all vertex buffer
	void SetNumberOfVertex( UINT numVertex );

	// Get vertex channel by index
	Channel* GetVertexChannel(UINT iChannel);

	// Get specific channel by type
	Channel* GetVertexChannel(StreamChannelType channelType, UINT index = 0);

	// Add vertex channel
	Channel* AddVertexChannel(StreamDataType streamType, StreamChannelType channelType, UINT numElement);

};




