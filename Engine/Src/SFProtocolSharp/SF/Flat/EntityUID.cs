// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct EntityUID : IFlatbufferObject
{
  private Struct __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public void __init(int _i, ByteBuffer _bb) { __p = new Struct(_i, _bb); }
  public EntityUID __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint EntityId { get { return __p.bb.GetUint(__p.bb_pos + 0); } }
  public uint ServerId { get { return __p.bb.GetUint(__p.bb_pos + 4); } }

  public static Offset<SF.Flat.EntityUID> CreateEntityUID(FlatBufferBuilder builder, uint EntityId, uint ServerId) {
    builder.Prep(4, 8);
    builder.PutUint(ServerId);
    builder.PutUint(EntityId);
    return new Offset<SF.Flat.EntityUID>(builder.Offset);
  }
}


}
