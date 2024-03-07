// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct GetUGCContentInfoRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static GetUGCContentInfoRes GetRootAsGetUGCContentInfoRes(ByteBuffer _bb) { return GetRootAsGetUGCContentInfoRes(_bb, new GetUGCContentInfoRes()); }
  public static GetUGCContentInfoRes GetRootAsGetUGCContentInfoRes(ByteBuffer _bb, GetUGCContentInfoRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public GetUGCContentInfoRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public byte UgcmetaData(int j) { int o = __p.__offset(6); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int UgcmetaDataLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetUgcmetaDataBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetUgcmetaDataBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetUgcmetaDataArray() { return __p.__vector_as_array<byte>(6); }

  public static Offset<SF.Flat.Game.GetUGCContentInfoRes> CreateGetUGCContentInfoRes(FlatBufferBuilder builder,
      uint result = 0,
      VectorOffset ugcmeta_dataOffset = default(VectorOffset)) {
    builder.StartTable(2);
    GetUGCContentInfoRes.AddUgcmetaData(builder, ugcmeta_dataOffset);
    GetUGCContentInfoRes.AddResult(builder, result);
    return GetUGCContentInfoRes.EndGetUGCContentInfoRes(builder);
  }

  public static void StartGetUGCContentInfoRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static void AddUgcmetaData(FlatBufferBuilder builder, VectorOffset ugcmetaDataOffset) { builder.AddOffset(1, ugcmetaDataOffset.Value, 0); }
  public static VectorOffset CreateUgcmetaDataVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateUgcmetaDataVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateUgcmetaDataVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateUgcmetaDataVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartUgcmetaDataVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.Game.GetUGCContentInfoRes> EndGetUGCContentInfoRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.GetUGCContentInfoRes>(o);
  }
}


static public class GetUGCContentInfoResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyVectorOfData(tablePos, 6 /*UgcmetaData*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
