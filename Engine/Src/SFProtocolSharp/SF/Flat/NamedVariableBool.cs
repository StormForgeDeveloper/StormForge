// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct NamedVariableBool : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static NamedVariableBool GetRootAsNamedVariableBool(ByteBuffer _bb) { return GetRootAsNamedVariableBool(_bb, new NamedVariableBool()); }
  public static NamedVariableBool GetRootAsNamedVariableBool(ByteBuffer _bb, NamedVariableBool obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public NamedVariableBool __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public bool Value { get { int o = __p.__offset(4); return o != 0 ? 0!=__p.bb.Get(o + __p.bb_pos) : (bool)false; } }

  public static Offset<SF.Flat.NamedVariableBool> CreateNamedVariableBool(FlatBufferBuilder builder,
      bool value = false) {
    builder.StartTable(1);
    NamedVariableBool.AddValue(builder, value);
    return NamedVariableBool.EndNamedVariableBool(builder);
  }

  public static void StartNamedVariableBool(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddValue(FlatBufferBuilder builder, bool value) { builder.AddBool(0, value, false); }
  public static Offset<SF.Flat.NamedVariableBool> EndNamedVariableBool(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.NamedVariableBool>(o);
  }
}


static public class NamedVariableBoolVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Value*/, 1 /*bool*/, 1, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
