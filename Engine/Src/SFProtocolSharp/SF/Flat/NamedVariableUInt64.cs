// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct NamedVariableUInt64 : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static NamedVariableUInt64 GetRootAsNamedVariableUInt64(ByteBuffer _bb) { return GetRootAsNamedVariableUInt64(_bb, new NamedVariableUInt64()); }
  public static NamedVariableUInt64 GetRootAsNamedVariableUInt64(ByteBuffer _bb, NamedVariableUInt64 obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public NamedVariableUInt64 __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong Value { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.NamedVariableUInt64> CreateNamedVariableUInt64(FlatBufferBuilder builder,
      ulong value = 0) {
    builder.StartTable(1);
    NamedVariableUInt64.AddValue(builder, value);
    return NamedVariableUInt64.EndNamedVariableUInt64(builder);
  }

  public static void StartNamedVariableUInt64(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddValue(FlatBufferBuilder builder, ulong value) { builder.AddUlong(0, value, 0); }
  public static Offset<SF.Flat.NamedVariableUInt64> EndNamedVariableUInt64(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.NamedVariableUInt64>(o);
  }
}


static public class NamedVariableUInt64Verify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Value*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}