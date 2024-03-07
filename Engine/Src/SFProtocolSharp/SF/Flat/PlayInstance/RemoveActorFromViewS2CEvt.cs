// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct RemoveActorFromViewS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static RemoveActorFromViewS2CEvt GetRootAsRemoveActorFromViewS2CEvt(ByteBuffer _bb) { return GetRootAsRemoveActorFromViewS2CEvt(_bb, new RemoveActorFromViewS2CEvt()); }
  public static RemoveActorFromViewS2CEvt GetRootAsRemoveActorFromViewS2CEvt(ByteBuffer _bb, RemoveActorFromViewS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public RemoveActorFromViewS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public uint ActorId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.PlayInstance.RemoveActorFromViewS2CEvt> CreateRemoveActorFromViewS2CEvt(FlatBufferBuilder builder,
      ulong play_instance_uid = 0,
      uint actor_id = 0) {
    builder.StartTable(2);
    RemoveActorFromViewS2CEvt.AddPlayInstanceUid(builder, play_instance_uid);
    RemoveActorFromViewS2CEvt.AddActorId(builder, actor_id);
    return RemoveActorFromViewS2CEvt.EndRemoveActorFromViewS2CEvt(builder);
  }

  public static void StartRemoveActorFromViewS2CEvt(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, ulong playInstanceUid) { builder.AddUlong(0, playInstanceUid, 0); }
  public static void AddActorId(FlatBufferBuilder builder, uint actorId) { builder.AddUint(1, actorId, 0); }
  public static Offset<SF.Flat.PlayInstance.RemoveActorFromViewS2CEvt> EndRemoveActorFromViewS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.RemoveActorFromViewS2CEvt>(o);
  }
}


static public class RemoveActorFromViewS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*ActorId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
