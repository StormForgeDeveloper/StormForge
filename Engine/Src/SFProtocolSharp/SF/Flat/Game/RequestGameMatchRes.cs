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

  public ulong TotalGem { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong TotalGameMoney { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.Game.RequestGameMatchRes> CreateRequestGameMatchRes(FlatBufferBuilder builder,
      ulong total_gem = 0,
      ulong total_game_money = 0) {
    builder.StartTable(2);
    RequestGameMatchRes.AddTotalGameMoney(builder, total_game_money);
    RequestGameMatchRes.AddTotalGem(builder, total_gem);
    return RequestGameMatchRes.EndRequestGameMatchRes(builder);
  }

  public static void StartRequestGameMatchRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddTotalGem(FlatBufferBuilder builder, ulong totalGem) { builder.AddUlong(0, totalGem, 0); }
  public static void AddTotalGameMoney(FlatBufferBuilder builder, ulong totalGameMoney) { builder.AddUlong(1, totalGameMoney, 0); }
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
      && verifier.VerifyField(tablePos, 4 /*TotalGem*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*TotalGameMoney*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
