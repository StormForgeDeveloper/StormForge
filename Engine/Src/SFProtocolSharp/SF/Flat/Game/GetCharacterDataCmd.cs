// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct GetCharacterDataCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static GetCharacterDataCmd GetRootAsGetCharacterDataCmd(ByteBuffer _bb) { return GetRootAsGetCharacterDataCmd(_bb, new GetCharacterDataCmd()); }
  public static GetCharacterDataCmd GetRootAsGetCharacterDataCmd(ByteBuffer _bb, GetCharacterDataCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public GetCharacterDataCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint CharacterId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.Game.GetCharacterDataCmd> CreateGetCharacterDataCmd(FlatBufferBuilder builder,
      uint character_id = 0) {
    builder.StartTable(1);
    GetCharacterDataCmd.AddCharacterId(builder, character_id);
    return GetCharacterDataCmd.EndGetCharacterDataCmd(builder);
  }

  public static void StartGetCharacterDataCmd(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddCharacterId(FlatBufferBuilder builder, uint characterId) { builder.AddUint(0, characterId, 0); }
  public static Offset<SF.Flat.Game.GetCharacterDataCmd> EndGetCharacterDataCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.GetCharacterDataCmd>(o);
  }
}


static public class GetCharacterDataCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*CharacterId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
