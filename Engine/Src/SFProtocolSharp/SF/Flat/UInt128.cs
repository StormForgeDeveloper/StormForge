// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct UInt128 : IFlatbufferObject
{
  private Struct __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public void __init(int _i, ByteBuffer _bb) { __p = new Struct(_i, _bb); }
  public UInt128 __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong Low { get { return __p.bb.GetUlong(__p.bb_pos + 0); } }
  public ulong High { get { return __p.bb.GetUlong(__p.bb_pos + 8); } }

  public static Offset<SF.Flat.UInt128> CreateUInt128(FlatBufferBuilder builder, ulong Low, ulong High) {
    builder.Prep(8, 16);
    builder.PutUlong(High);
    builder.PutUlong(Low);
    return new Offset<SF.Flat.UInt128>(builder.Offset);
  }
}


}
