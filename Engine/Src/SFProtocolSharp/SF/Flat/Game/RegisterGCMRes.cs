// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct RegisterGCMRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static RegisterGCMRes GetRootAsRegisterGCMRes(ByteBuffer _bb) { return GetRootAsRegisterGCMRes(_bb, new RegisterGCMRes()); }
  public static RegisterGCMRes GetRootAsRegisterGCMRes(ByteBuffer _bb, RegisterGCMRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public RegisterGCMRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.Game.RegisterGCMRes> CreateRegisterGCMRes(FlatBufferBuilder builder,
      uint result = 0) {
    builder.StartTable(1);
    RegisterGCMRes.AddResult(builder, result);
    return RegisterGCMRes.EndRegisterGCMRes(builder);
  }

  public static void StartRegisterGCMRes(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static Offset<SF.Flat.Game.RegisterGCMRes> EndRegisterGCMRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.RegisterGCMRes>(o);
  }
}


static public class RegisterGCMResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
