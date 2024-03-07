// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct SaveUGCRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static SaveUGCRes GetRootAsSaveUGCRes(ByteBuffer _bb) { return GetRootAsSaveUGCRes(_bb, new SaveUGCRes()); }
  public static SaveUGCRes GetRootAsSaveUGCRes(ByteBuffer _bb, SaveUGCRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public SaveUGCRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public ulong Ugcid { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.Game.SaveUGCRes> CreateSaveUGCRes(FlatBufferBuilder builder,
      uint result = 0,
      ulong ugcid = 0) {
    builder.StartTable(2);
    SaveUGCRes.AddUgcid(builder, ugcid);
    SaveUGCRes.AddResult(builder, result);
    return SaveUGCRes.EndSaveUGCRes(builder);
  }

  public static void StartSaveUGCRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static void AddUgcid(FlatBufferBuilder builder, ulong ugcid) { builder.AddUlong(1, ugcid, 0); }
  public static Offset<SF.Flat.Game.SaveUGCRes> EndSaveUGCRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.SaveUGCRes>(o);
  }
}


static public class SaveUGCResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*Ugcid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
