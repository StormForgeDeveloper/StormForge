// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct ActorMovementS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static ActorMovementS2CEvt GetRootAsActorMovementS2CEvt(ByteBuffer _bb) { return GetRootAsActorMovementS2CEvt(_bb, new ActorMovementS2CEvt()); }
  public static ActorMovementS2CEvt GetRootAsActorMovementS2CEvt(ByteBuffer _bb, ActorMovementS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public ActorMovementS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public SF.Flat.ActorMovement? Movement { get { int o = __p.__offset(6); return o != 0 ? (SF.Flat.ActorMovement?)(new SF.Flat.ActorMovement()).__assign(__p.__indirect(o + __p.bb_pos), __p.bb) : null; } }

  public static Offset<SF.Flat.PlayInstance.ActorMovementS2CEvt> CreateActorMovementS2CEvt(FlatBufferBuilder builder,
      ulong play_instance_uid = 0,
      Offset<SF.Flat.ActorMovement> movementOffset = default(Offset<SF.Flat.ActorMovement>)) {
    builder.StartTable(2);
    ActorMovementS2CEvt.AddPlayInstanceUid(builder, play_instance_uid);
    ActorMovementS2CEvt.AddMovement(builder, movementOffset);
    return ActorMovementS2CEvt.EndActorMovementS2CEvt(builder);
  }

  public static void StartActorMovementS2CEvt(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, ulong playInstanceUid) { builder.AddUlong(0, playInstanceUid, 0); }
  public static void AddMovement(FlatBufferBuilder builder, Offset<SF.Flat.ActorMovement> movementOffset) { builder.AddOffset(1, movementOffset.Value, 0); }
  public static Offset<SF.Flat.PlayInstance.ActorMovementS2CEvt> EndActorMovementS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.ActorMovementS2CEvt>(o);
  }
}


static public class ActorMovementS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTable(tablePos, 6 /*Movement*/, SF.Flat.ActorMovementVerify.Verify, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
