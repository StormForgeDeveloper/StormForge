// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct GetAchievementStatsRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static GetAchievementStatsRes GetRootAsGetAchievementStatsRes(ByteBuffer _bb) { return GetRootAsGetAchievementStatsRes(_bb, new GetAchievementStatsRes()); }
  public static GetAchievementStatsRes GetRootAsGetAchievementStatsRes(ByteBuffer _bb, GetAchievementStatsRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public GetAchievementStatsRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public SF.Flat.AchievementStat? AchievementStats(int j) { int o = __p.__offset(6); return o != 0 ? (SF.Flat.AchievementStat?)(new SF.Flat.AchievementStat()).__assign(__p.__indirect(__p.__vector(o) + j * 4), __p.bb) : null; }
  public int AchievementStatsLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }

  public static Offset<SF.Flat.Game.GetAchievementStatsRes> CreateGetAchievementStatsRes(FlatBufferBuilder builder,
      uint result = 0,
      VectorOffset achievement_statsOffset = default(VectorOffset)) {
    builder.StartTable(2);
    GetAchievementStatsRes.AddAchievementStats(builder, achievement_statsOffset);
    GetAchievementStatsRes.AddResult(builder, result);
    return GetAchievementStatsRes.EndGetAchievementStatsRes(builder);
  }

  public static void StartGetAchievementStatsRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static void AddAchievementStats(FlatBufferBuilder builder, VectorOffset achievementStatsOffset) { builder.AddOffset(1, achievementStatsOffset.Value, 0); }
  public static VectorOffset CreateAchievementStatsVector(FlatBufferBuilder builder, Offset<SF.Flat.AchievementStat>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static VectorOffset CreateAchievementStatsVectorBlock(FlatBufferBuilder builder, Offset<SF.Flat.AchievementStat>[] data) { builder.StartVector(4, data.Length, 4); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateAchievementStatsVectorBlock(FlatBufferBuilder builder, ArraySegment<Offset<SF.Flat.AchievementStat>> data) { builder.StartVector(4, data.Count, 4); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateAchievementStatsVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<Offset<SF.Flat.AchievementStat>>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartAchievementStatsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<SF.Flat.Game.GetAchievementStatsRes> EndGetAchievementStatsRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.GetAchievementStatsRes>(o);
  }
}


static public class GetAchievementStatsResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyVectorOfTables(tablePos, 6 /*AchievementStats*/, SF.Flat.AchievementStatVerify.Verify, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
