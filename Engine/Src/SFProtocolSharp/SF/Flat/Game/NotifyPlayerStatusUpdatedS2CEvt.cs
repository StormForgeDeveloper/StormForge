// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct NotifyPlayerStatusUpdatedS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static NotifyPlayerStatusUpdatedS2CEvt GetRootAsNotifyPlayerStatusUpdatedS2CEvt(ByteBuffer _bb) { return GetRootAsNotifyPlayerStatusUpdatedS2CEvt(_bb, new NotifyPlayerStatusUpdatedS2CEvt()); }
  public static NotifyPlayerStatusUpdatedS2CEvt GetRootAsNotifyPlayerStatusUpdatedS2CEvt(ByteBuffer _bb, NotifyPlayerStatusUpdatedS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public NotifyPlayerStatusUpdatedS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PlayerId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public uint LatestActiveTime { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public byte IsInGame { get { int o = __p.__offset(8); return o != 0 ? __p.bb.Get(o + __p.bb_pos) : (byte)0; } }

  public static Offset<SF.Flat.Game.NotifyPlayerStatusUpdatedS2CEvt> CreateNotifyPlayerStatusUpdatedS2CEvt(FlatBufferBuilder builder,
      ulong player_id = 0,
      uint latest_active_time = 0,
      byte is_in_game = 0) {
    builder.StartTable(3);
    NotifyPlayerStatusUpdatedS2CEvt.AddPlayerId(builder, player_id);
    NotifyPlayerStatusUpdatedS2CEvt.AddLatestActiveTime(builder, latest_active_time);
    NotifyPlayerStatusUpdatedS2CEvt.AddIsInGame(builder, is_in_game);
    return NotifyPlayerStatusUpdatedS2CEvt.EndNotifyPlayerStatusUpdatedS2CEvt(builder);
  }

  public static void StartNotifyPlayerStatusUpdatedS2CEvt(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddPlayerId(FlatBufferBuilder builder, ulong playerId) { builder.AddUlong(0, playerId, 0); }
  public static void AddLatestActiveTime(FlatBufferBuilder builder, uint latestActiveTime) { builder.AddUint(1, latestActiveTime, 0); }
  public static void AddIsInGame(FlatBufferBuilder builder, byte isInGame) { builder.AddByte(2, isInGame, 0); }
  public static Offset<SF.Flat.Game.NotifyPlayerStatusUpdatedS2CEvt> EndNotifyPlayerStatusUpdatedS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.NotifyPlayerStatusUpdatedS2CEvt>(o);
  }
}


static public class NotifyPlayerStatusUpdatedS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*LatestActiveTime*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 8 /*IsInGame*/, 1 /*byte*/, 1, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}