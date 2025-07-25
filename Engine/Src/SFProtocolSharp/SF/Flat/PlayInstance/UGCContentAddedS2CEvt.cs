// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct UGCContentAddedS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static UGCContentAddedS2CEvt GetRootAsUGCContentAddedS2CEvt(ByteBuffer _bb) { return GetRootAsUGCContentAddedS2CEvt(_bb, new UGCContentAddedS2CEvt()); }
  public static UGCContentAddedS2CEvt GetRootAsUGCContentAddedS2CEvt(ByteBuffer _bb, UGCContentAddedS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public UGCContentAddedS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public SF.Flat.AccountID? OwnerAccount { get { int o = __p.__offset(4); return o != 0 ? (SF.Flat.AccountID?)(new SF.Flat.AccountID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public string Category { get { int o = __p.__offset(6); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetCategoryBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetCategoryBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetCategoryArray() { return __p.__vector_as_array<byte>(6); }
  public ulong DataId { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public SF.Flat.Guid? ContentGuid { get { int o = __p.__offset(10); return o != 0 ? (SF.Flat.Guid?)(new SF.Flat.Guid()).__assign(o + __p.bb_pos, __p.bb) : null; } }

  public static void StartUGCContentAddedS2CEvt(FlatBufferBuilder builder) { builder.StartTable(4); }
  public static void AddOwnerAccount(FlatBufferBuilder builder, Offset<SF.Flat.AccountID> ownerAccountOffset) { builder.AddStruct(0, ownerAccountOffset.Value, 0); }
  public static void AddCategory(FlatBufferBuilder builder, StringOffset categoryOffset) { builder.AddOffset(1, categoryOffset.Value, 0); }
  public static void AddDataId(FlatBufferBuilder builder, ulong dataId) { builder.AddUlong(2, dataId, 0); }
  public static void AddContentGuid(FlatBufferBuilder builder, Offset<SF.Flat.Guid> contentGuidOffset) { builder.AddStruct(3, contentGuidOffset.Value, 0); }
  public static Offset<SF.Flat.PlayInstance.UGCContentAddedS2CEvt> EndUGCContentAddedS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.UGCContentAddedS2CEvt>(o);
  }
}


static public class UGCContentAddedS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*OwnerAccount*/, 16 /*SF.Flat.AccountID*/, 8, false)
      && verifier.VerifyString(tablePos, 6 /*Category*/, false)
      && verifier.VerifyField(tablePos, 8 /*DataId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 10 /*ContentGuid*/, 16 /*SF.Flat.Guid*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
