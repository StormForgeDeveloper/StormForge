// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct NamedVariableGuid : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static NamedVariableGuid GetRootAsNamedVariableGuid(ByteBuffer _bb) { return GetRootAsNamedVariableGuid(_bb, new NamedVariableGuid()); }
  public static NamedVariableGuid GetRootAsNamedVariableGuid(ByteBuffer _bb, NamedVariableGuid obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public NamedVariableGuid __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public SF.Flat.Guid? Value { get { int o = __p.__offset(4); return o != 0 ? (SF.Flat.Guid?)(new SF.Flat.Guid()).__assign(o + __p.bb_pos, __p.bb) : null; } }

  public static void StartNamedVariableGuid(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddValue(FlatBufferBuilder builder, Offset<SF.Flat.Guid> valueOffset) { builder.AddStruct(0, valueOffset.Value, 0); }
  public static Offset<SF.Flat.NamedVariableGuid> EndNamedVariableGuid(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.NamedVariableGuid>(o);
  }
}


static public class NamedVariableGuidVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Value*/, 16 /*SF.Flat.Guid*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}