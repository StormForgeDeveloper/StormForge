// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct DeleteCharacterRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static DeleteCharacterRes GetRootAsDeleteCharacterRes(ByteBuffer _bb) { return GetRootAsDeleteCharacterRes(_bb, new DeleteCharacterRes()); }
  public static DeleteCharacterRes GetRootAsDeleteCharacterRes(ByteBuffer _bb, DeleteCharacterRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public DeleteCharacterRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.Game.DeleteCharacterRes> CreateDeleteCharacterRes(FlatBufferBuilder builder,
      uint result = 0) {
    builder.StartTable(1);
    DeleteCharacterRes.AddResult(builder, result);
    return DeleteCharacterRes.EndDeleteCharacterRes(builder);
  }

  public static void StartDeleteCharacterRes(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static Offset<SF.Flat.Game.DeleteCharacterRes> EndDeleteCharacterRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.DeleteCharacterRes>(o);
  }
}


static public class DeleteCharacterResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
