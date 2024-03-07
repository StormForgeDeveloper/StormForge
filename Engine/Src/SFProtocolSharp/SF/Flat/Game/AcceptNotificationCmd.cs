// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct AcceptNotificationCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static AcceptNotificationCmd GetRootAsAcceptNotificationCmd(ByteBuffer _bb) { return GetRootAsAcceptNotificationCmd(_bb, new AcceptNotificationCmd()); }
  public static AcceptNotificationCmd GetRootAsAcceptNotificationCmd(ByteBuffer _bb, AcceptNotificationCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public AcceptNotificationCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint NotificationId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.Game.AcceptNotificationCmd> CreateAcceptNotificationCmd(FlatBufferBuilder builder,
      uint notification_id = 0) {
    builder.StartTable(1);
    AcceptNotificationCmd.AddNotificationId(builder, notification_id);
    return AcceptNotificationCmd.EndAcceptNotificationCmd(builder);
  }

  public static void StartAcceptNotificationCmd(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddNotificationId(FlatBufferBuilder builder, uint notificationId) { builder.AddUint(0, notificationId, 0); }
  public static Offset<SF.Flat.Game.AcceptNotificationCmd> EndAcceptNotificationCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.AcceptNotificationCmd>(o);
  }
}


static public class AcceptNotificationCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*NotificationId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
