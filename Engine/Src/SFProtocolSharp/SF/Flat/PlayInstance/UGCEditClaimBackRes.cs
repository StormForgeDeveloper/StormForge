// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct UGCEditClaimBackRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static UGCEditClaimBackRes GetRootAsUGCEditClaimBackRes(ByteBuffer _bb) { return GetRootAsUGCEditClaimBackRes(_bb, new UGCEditClaimBackRes()); }
  public static UGCEditClaimBackRes GetRootAsUGCEditClaimBackRes(ByteBuffer _bb, UGCEditClaimBackRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public UGCEditClaimBackRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint EntityInstanceId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public uint GroupInstanceId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public byte InvenChanges(int j) { int o = __p.__offset(8); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int InvenChangesLength { get { int o = __p.__offset(8); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetInvenChangesBytes() { return __p.__vector_as_span<byte>(8, 1); }
#else
  public ArraySegment<byte>? GetInvenChangesBytes() { return __p.__vector_as_arraysegment(8); }
#endif
  public byte[] GetInvenChangesArray() { return __p.__vector_as_array<byte>(8); }

  public static Offset<SF.Flat.PlayInstance.UGCEditClaimBackRes> CreateUGCEditClaimBackRes(FlatBufferBuilder builder,
      uint entity_instance_id = 0,
      uint group_instance_id = 0,
      VectorOffset inven_changesOffset = default(VectorOffset)) {
    builder.StartTable(3);
    UGCEditClaimBackRes.AddInvenChanges(builder, inven_changesOffset);
    UGCEditClaimBackRes.AddGroupInstanceId(builder, group_instance_id);
    UGCEditClaimBackRes.AddEntityInstanceId(builder, entity_instance_id);
    return UGCEditClaimBackRes.EndUGCEditClaimBackRes(builder);
  }

  public static void StartUGCEditClaimBackRes(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddEntityInstanceId(FlatBufferBuilder builder, uint entityInstanceId) { builder.AddUint(0, entityInstanceId, 0); }
  public static void AddGroupInstanceId(FlatBufferBuilder builder, uint groupInstanceId) { builder.AddUint(1, groupInstanceId, 0); }
  public static void AddInvenChanges(FlatBufferBuilder builder, VectorOffset invenChangesOffset) { builder.AddOffset(2, invenChangesOffset.Value, 0); }
  public static VectorOffset CreateInvenChangesVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateInvenChangesVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateInvenChangesVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateInvenChangesVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartInvenChangesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.PlayInstance.UGCEditClaimBackRes> EndUGCEditClaimBackRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.UGCEditClaimBackRes>(o);
  }
}


static public class UGCEditClaimBackResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*EntityInstanceId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*GroupInstanceId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyVectorOfData(tablePos, 8 /*InvenChanges*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
