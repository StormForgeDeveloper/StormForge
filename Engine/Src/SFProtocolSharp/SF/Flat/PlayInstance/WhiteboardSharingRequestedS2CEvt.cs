// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct WhiteboardSharingRequestedS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static WhiteboardSharingRequestedS2CEvt GetRootAsWhiteboardSharingRequestedS2CEvt(ByteBuffer _bb) { return GetRootAsWhiteboardSharingRequestedS2CEvt(_bb, new WhiteboardSharingRequestedS2CEvt()); }
  public static WhiteboardSharingRequestedS2CEvt GetRootAsWhiteboardSharingRequestedS2CEvt(ByteBuffer _bb, WhiteboardSharingRequestedS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public WhiteboardSharingRequestedS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong PlayerId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong RequestedPlayerId { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.PlayInstance.WhiteboardSharingRequestedS2CEvt> CreateWhiteboardSharingRequestedS2CEvt(FlatBufferBuilder builder,
      ulong play_instance_uid = 0,
      ulong player_id = 0,
      ulong requested_player_id = 0) {
    builder.StartTable(3);
    WhiteboardSharingRequestedS2CEvt.AddRequestedPlayerId(builder, requested_player_id);
    WhiteboardSharingRequestedS2CEvt.AddPlayerId(builder, player_id);
    WhiteboardSharingRequestedS2CEvt.AddPlayInstanceUid(builder, play_instance_uid);
    return WhiteboardSharingRequestedS2CEvt.EndWhiteboardSharingRequestedS2CEvt(builder);
  }

  public static void StartWhiteboardSharingRequestedS2CEvt(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, ulong playInstanceUid) { builder.AddUlong(0, playInstanceUid, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, ulong playerId) { builder.AddUlong(1, playerId, 0); }
  public static void AddRequestedPlayerId(FlatBufferBuilder builder, ulong requestedPlayerId) { builder.AddUlong(2, requestedPlayerId, 0); }
  public static Offset<SF.Flat.PlayInstance.WhiteboardSharingRequestedS2CEvt> EndWhiteboardSharingRequestedS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.WhiteboardSharingRequestedS2CEvt>(o);
  }
}


static public class WhiteboardSharingRequestedS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 8 /*RequestedPlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
