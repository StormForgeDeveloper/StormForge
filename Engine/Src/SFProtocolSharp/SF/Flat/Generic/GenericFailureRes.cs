// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Generic
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct GenericFailureRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static GenericFailureRes GetRootAsGenericFailureRes(ByteBuffer _bb) { return GetRootAsGenericFailureRes(_bb, new GenericFailureRes()); }
  public static GenericFailureRes GetRootAsGenericFailureRes(ByteBuffer _bb, GenericFailureRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public GenericFailureRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }


  public static void StartGenericFailureRes(FlatBufferBuilder builder) { builder.StartTable(0); }
  public static Offset<SF.Flat.Generic.GenericFailureRes> EndGenericFailureRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Generic.GenericFailureRes>(o);
  }
}


static public class GenericFailureResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
