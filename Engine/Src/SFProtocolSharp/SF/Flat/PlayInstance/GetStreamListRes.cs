// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct GetStreamListRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static GetStreamListRes GetRootAsGetStreamListRes(ByteBuffer _bb) { return GetRootAsGetStreamListRes(_bb, new GetStreamListRes()); }
  public static GetStreamListRes GetRootAsGetStreamListRes(ByteBuffer _bb, GetStreamListRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public static bool VerifyGetStreamListRes(ByteBuffer _bb) {Google.FlatBuffers.Verifier verifier = new Google.FlatBuffers.Verifier(_bb); return verifier.VerifyBuffer("", false, GetStreamListResVerify.Verify); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public GetStreamListRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public string StreamNames(int j) { int o = __p.__offset(4); return o != 0 ? __p.__string(__p.__vector(o) + j * 4) : null; }
  public int StreamNamesLength { get { int o = __p.__offset(4); return o != 0 ? __p.__vector_len(o) : 0; } }

  public static Offset<SF.Flat.PlayInstance.GetStreamListRes> CreateGetStreamListRes(FlatBufferBuilder builder,
      VectorOffset stream_namesOffset = default(VectorOffset)) {
    builder.StartTable(1);
    GetStreamListRes.AddStreamNames(builder, stream_namesOffset);
    return GetStreamListRes.EndGetStreamListRes(builder);
  }

  public static void StartGetStreamListRes(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddStreamNames(FlatBufferBuilder builder, VectorOffset streamNamesOffset) { builder.AddOffset(0, streamNamesOffset.Value, 0); }
  public static VectorOffset CreateStreamNamesVector(FlatBufferBuilder builder, StringOffset[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static VectorOffset CreateStreamNamesVectorBlock(FlatBufferBuilder builder, StringOffset[] data) { builder.StartVector(4, data.Length, 4); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateStreamNamesVectorBlock(FlatBufferBuilder builder, ArraySegment<StringOffset> data) { builder.StartVector(4, data.Count, 4); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateStreamNamesVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<StringOffset>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartStreamNamesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<SF.Flat.PlayInstance.GetStreamListRes> EndGetStreamListRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.GetStreamListRes>(o);
  }
  public static void FinishGetStreamListResBuffer(FlatBufferBuilder builder, Offset<SF.Flat.PlayInstance.GetStreamListRes> offset) { builder.Finish(offset.Value); }
  public static void FinishSizePrefixedGetStreamListResBuffer(FlatBufferBuilder builder, Offset<SF.Flat.PlayInstance.GetStreamListRes> offset) { builder.FinishSizePrefixed(offset.Value); }
}


static public class GetStreamListResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyVectorOfStrings(tablePos, 4 /*StreamNames*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
