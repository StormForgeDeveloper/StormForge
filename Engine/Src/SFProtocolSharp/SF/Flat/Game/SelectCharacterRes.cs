// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct SelectCharacterRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static SelectCharacterRes GetRootAsSelectCharacterRes(ByteBuffer _bb) { return GetRootAsSelectCharacterRes(_bb, new SelectCharacterRes()); }
  public static SelectCharacterRes GetRootAsSelectCharacterRes(ByteBuffer _bb, SelectCharacterRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public SelectCharacterRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public SF.Flat.CharacterID? CharacterId { get { int o = __p.__offset(4); return o != 0 ? (SF.Flat.CharacterID?)(new SF.Flat.CharacterID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public byte Attributes(int j) { int o = __p.__offset(6); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int AttributesLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetAttributesBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetAttributesBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetAttributesArray() { return __p.__vector_as_array<byte>(6); }

  public static void StartSelectCharacterRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddCharacterId(FlatBufferBuilder builder, Offset<SF.Flat.CharacterID> characterIdOffset) { builder.AddStruct(0, characterIdOffset.Value, 0); }
  public static void AddAttributes(FlatBufferBuilder builder, VectorOffset attributesOffset) { builder.AddOffset(1, attributesOffset.Value, 0); }
  public static VectorOffset CreateAttributesVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateAttributesVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateAttributesVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateAttributesVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartAttributesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.Game.SelectCharacterRes> EndSelectCharacterRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.SelectCharacterRes>(o);
  }
}


static public class SelectCharacterResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*CharacterId*/, 16 /*SF.Flat.CharacterID*/, 8, false)
      && verifier.VerifyVectorOfData(tablePos, 6 /*Attributes*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
