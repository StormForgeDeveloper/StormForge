// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct LeavePartyRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static LeavePartyRes GetRootAsLeavePartyRes(ByteBuffer _bb) { return GetRootAsLeavePartyRes(_bb, new LeavePartyRes()); }
  public static LeavePartyRes GetRootAsLeavePartyRes(ByteBuffer _bb, LeavePartyRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public LeavePartyRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.Game.LeavePartyRes> CreateLeavePartyRes(FlatBufferBuilder builder,
      uint result = 0) {
    builder.StartTable(1);
    LeavePartyRes.AddResult(builder, result);
    return LeavePartyRes.EndLeavePartyRes(builder);
  }

  public static void StartLeavePartyRes(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static Offset<SF.Flat.Game.LeavePartyRes> EndLeavePartyRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.LeavePartyRes>(o);
  }
}


static public class LeavePartyResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
