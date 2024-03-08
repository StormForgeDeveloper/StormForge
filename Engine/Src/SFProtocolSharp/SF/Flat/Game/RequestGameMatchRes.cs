// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct RequestGameMatchRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static RequestGameMatchRes GetRootAsRequestGameMatchRes(ByteBuffer _bb) { return GetRootAsRequestGameMatchRes(_bb, new RequestGameMatchRes()); }
  public static RequestGameMatchRes GetRootAsRequestGameMatchRes(ByteBuffer _bb, RequestGameMatchRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public RequestGameMatchRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public ulong TotalGem { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong TotalGameMoney { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.Game.RequestGameMatchRes> CreateRequestGameMatchRes(FlatBufferBuilder builder,
      uint result = 0,
      ulong total_gem = 0,
      ulong total_game_money = 0) {
    builder.StartTable(3);
    RequestGameMatchRes.AddTotalGameMoney(builder, total_game_money);
    RequestGameMatchRes.AddTotalGem(builder, total_gem);
    RequestGameMatchRes.AddResult(builder, result);
    return RequestGameMatchRes.EndRequestGameMatchRes(builder);
  }

  public static void StartRequestGameMatchRes(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static void AddTotalGem(FlatBufferBuilder builder, ulong totalGem) { builder.AddUlong(1, totalGem, 0); }
  public static void AddTotalGameMoney(FlatBufferBuilder builder, ulong totalGameMoney) { builder.AddUlong(2, totalGameMoney, 0); }
  public static Offset<SF.Flat.Game.RequestGameMatchRes> EndRequestGameMatchRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.RequestGameMatchRes>(o);
  }
}


static public class RequestGameMatchResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*TotalGem*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 8 /*TotalGameMoney*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
