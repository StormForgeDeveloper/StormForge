// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct OccupyMapObjectRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static OccupyMapObjectRes GetRootAsOccupyMapObjectRes(ByteBuffer _bb) { return GetRootAsOccupyMapObjectRes(_bb, new OccupyMapObjectRes()); }
  public static OccupyMapObjectRes GetRootAsOccupyMapObjectRes(ByteBuffer _bb, OccupyMapObjectRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public OccupyMapObjectRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public ulong PlayInstanceUid { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong PlayerId { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public uint MapObjectId { get { int o = __p.__offset(10); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.PlayInstance.OccupyMapObjectRes> CreateOccupyMapObjectRes(FlatBufferBuilder builder,
      uint result = 0,
      ulong play_instance_uid = 0,
      ulong player_id = 0,
      uint map_object_id = 0) {
    builder.StartTable(4);
    OccupyMapObjectRes.AddPlayerId(builder, player_id);
    OccupyMapObjectRes.AddPlayInstanceUid(builder, play_instance_uid);
    OccupyMapObjectRes.AddMapObjectId(builder, map_object_id);
    OccupyMapObjectRes.AddResult(builder, result);
    return OccupyMapObjectRes.EndOccupyMapObjectRes(builder);
  }

  public static void StartOccupyMapObjectRes(FlatBufferBuilder builder) { builder.StartTable(4); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, ulong playInstanceUid) { builder.AddUlong(1, playInstanceUid, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, ulong playerId) { builder.AddUlong(2, playerId, 0); }
  public static void AddMapObjectId(FlatBufferBuilder builder, uint mapObjectId) { builder.AddUint(3, mapObjectId, 0); }
  public static Offset<SF.Flat.PlayInstance.OccupyMapObjectRes> EndOccupyMapObjectRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.OccupyMapObjectRes>(o);
  }
}


static public class OccupyMapObjectResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*PlayInstanceUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 8 /*PlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 10 /*MapObjectId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}