// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct VoiceDataS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static VoiceDataS2CEvt GetRootAsVoiceDataS2CEvt(ByteBuffer _bb) { return GetRootAsVoiceDataS2CEvt(_bb, new VoiceDataS2CEvt()); }
  public static VoiceDataS2CEvt GetRootAsVoiceDataS2CEvt(ByteBuffer _bb, VoiceDataS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public VoiceDataS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint ActorId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public ushort FrameIndex { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUshort(o + __p.bb_pos) : (ushort)0; } }
  public byte VoiceData(int j) { int o = __p.__offset(8); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int VoiceDataLength { get { int o = __p.__offset(8); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetVoiceDataBytes() { return __p.__vector_as_span<byte>(8, 1); }
#else
  public ArraySegment<byte>? GetVoiceDataBytes() { return __p.__vector_as_arraysegment(8); }
#endif
  public byte[] GetVoiceDataArray() { return __p.__vector_as_array<byte>(8); }

  public static Offset<SF.Flat.PlayInstance.VoiceDataS2CEvt> CreateVoiceDataS2CEvt(FlatBufferBuilder builder,
      uint actor_id = 0,
      ushort frame_index = 0,
      VectorOffset voice_dataOffset = default(VectorOffset)) {
    builder.StartTable(3);
    VoiceDataS2CEvt.AddVoiceData(builder, voice_dataOffset);
    VoiceDataS2CEvt.AddActorId(builder, actor_id);
    VoiceDataS2CEvt.AddFrameIndex(builder, frame_index);
    return VoiceDataS2CEvt.EndVoiceDataS2CEvt(builder);
  }

  public static void StartVoiceDataS2CEvt(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddActorId(FlatBufferBuilder builder, uint actorId) { builder.AddUint(0, actorId, 0); }
  public static void AddFrameIndex(FlatBufferBuilder builder, ushort frameIndex) { builder.AddUshort(1, frameIndex, 0); }
  public static void AddVoiceData(FlatBufferBuilder builder, VectorOffset voiceDataOffset) { builder.AddOffset(2, voiceDataOffset.Value, 0); }
  public static VectorOffset CreateVoiceDataVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateVoiceDataVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateVoiceDataVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateVoiceDataVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartVoiceDataVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.PlayInstance.VoiceDataS2CEvt> EndVoiceDataS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.VoiceDataS2CEvt>(o);
  }
}


static public class VoiceDataS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*ActorId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*FrameIndex*/, 2 /*ushort*/, 2, false)
      && verifier.VerifyVectorOfData(tablePos, 8 /*VoiceData*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
