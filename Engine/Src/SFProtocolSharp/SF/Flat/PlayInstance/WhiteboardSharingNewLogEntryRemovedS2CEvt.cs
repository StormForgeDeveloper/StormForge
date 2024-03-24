// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct WhiteboardSharingNewLogEntryRemovedS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static WhiteboardSharingNewLogEntryRemovedS2CEvt GetRootAsWhiteboardSharingNewLogEntryRemovedS2CEvt(ByteBuffer _bb) { return GetRootAsWhiteboardSharingNewLogEntryRemovedS2CEvt(_bb, new WhiteboardSharingNewLogEntryRemovedS2CEvt()); }
  public static WhiteboardSharingNewLogEntryRemovedS2CEvt GetRootAsWhiteboardSharingNewLogEntryRemovedS2CEvt(ByteBuffer _bb, WhiteboardSharingNewLogEntryRemovedS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public WhiteboardSharingNewLogEntryRemovedS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public SF.Flat.EntityUID? PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? (SF.Flat.EntityUID?)(new SF.Flat.EntityUID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public SF.Flat.AccountID? PlayerId { get { int o = __p.__offset(6); return o != 0 ? (SF.Flat.AccountID?)(new SF.Flat.AccountID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public uint LogEntryId { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static void StartWhiteboardSharingNewLogEntryRemovedS2CEvt(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, Offset<SF.Flat.EntityUID> playInstanceUidOffset) { builder.AddStruct(0, playInstanceUidOffset.Value, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, Offset<SF.Flat.AccountID> playerIdOffset) { builder.AddStruct(1, playerIdOffset.Value, 0); }
  public static void AddLogEntryId(FlatBufferBuilder builder, uint logEntryId) { builder.AddUint(2, logEntryId, 0); }
  public static Offset<SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryRemovedS2CEvt> EndWhiteboardSharingNewLogEntryRemovedS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryRemovedS2CEvt>(o);
  }
}


static public class WhiteboardSharingNewLogEntryRemovedS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 4 /*SF.Flat.EntityUID*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 16 /*SF.Flat.AccountID*/, 8, false)
      && verifier.VerifyField(tablePos, 8 /*LogEntryId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
