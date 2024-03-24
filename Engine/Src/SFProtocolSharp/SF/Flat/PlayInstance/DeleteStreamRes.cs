// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct DeleteStreamRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static DeleteStreamRes GetRootAsDeleteStreamRes(ByteBuffer _bb) { return GetRootAsDeleteStreamRes(_bb, new DeleteStreamRes()); }
  public static DeleteStreamRes GetRootAsDeleteStreamRes(ByteBuffer _bb, DeleteStreamRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public DeleteStreamRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public string StreamName { get { int o = __p.__offset(6); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetStreamNameBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetStreamNameBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetStreamNameArray() { return __p.__vector_as_array<byte>(6); }

  public static Offset<SF.Flat.PlayInstance.DeleteStreamRes> CreateDeleteStreamRes(FlatBufferBuilder builder,
      int result = 0,
      StringOffset stream_nameOffset = default(StringOffset)) {
    builder.StartTable(2);
    DeleteStreamRes.AddStreamName(builder, stream_nameOffset);
    DeleteStreamRes.AddResult(builder, result);
    return DeleteStreamRes.EndDeleteStreamRes(builder);
  }

  public static void StartDeleteStreamRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddResult(FlatBufferBuilder builder, int result) { builder.AddInt(0, result, 0); }
  public static void AddStreamName(FlatBufferBuilder builder, StringOffset streamNameOffset) { builder.AddOffset(1, streamNameOffset.Value, 0); }
  public static Offset<SF.Flat.PlayInstance.DeleteStreamRes> EndDeleteStreamRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.DeleteStreamRes>(o);
  }
}


static public class DeleteStreamResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*int*/, 4, false)
      && verifier.VerifyString(tablePos, 6 /*StreamName*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
