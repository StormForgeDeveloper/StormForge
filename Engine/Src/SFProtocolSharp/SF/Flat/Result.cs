// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct Result : IFlatbufferObject
{
  private Struct __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public void __init(int _i, ByteBuffer _bb) { __p = new Struct(_i, _bb); }
  public Result __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int Value { get { return __p.bb.GetInt(__p.bb_pos + 0); } }

  public static Offset<SF.Flat.Result> CreateResult(FlatBufferBuilder builder, int Value) {
    builder.Prep(4, 4);
    builder.PutInt(Value);
    return new Offset<SF.Flat.Result>(builder.Offset);
  }
}


}
