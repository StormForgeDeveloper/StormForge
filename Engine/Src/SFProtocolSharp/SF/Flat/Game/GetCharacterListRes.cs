// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct GetCharacterListRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static GetCharacterListRes GetRootAsGetCharacterListRes(ByteBuffer _bb) { return GetRootAsGetCharacterListRes(_bb, new GetCharacterListRes()); }
  public static GetCharacterListRes GetRootAsGetCharacterListRes(ByteBuffer _bb, GetCharacterListRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public GetCharacterListRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public byte Characters(int j) { int o = __p.__offset(6); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int CharactersLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetCharactersBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetCharactersBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetCharactersArray() { return __p.__vector_as_array<byte>(6); }

  public static Offset<SF.Flat.Game.GetCharacterListRes> CreateGetCharacterListRes(FlatBufferBuilder builder,
      uint result = 0,
      VectorOffset charactersOffset = default(VectorOffset)) {
    builder.StartTable(2);
    GetCharacterListRes.AddCharacters(builder, charactersOffset);
    GetCharacterListRes.AddResult(builder, result);
    return GetCharacterListRes.EndGetCharacterListRes(builder);
  }

  public static void StartGetCharacterListRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static void AddCharacters(FlatBufferBuilder builder, VectorOffset charactersOffset) { builder.AddOffset(1, charactersOffset.Value, 0); }
  public static VectorOffset CreateCharactersVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateCharactersVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateCharactersVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateCharactersVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartCharactersVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.Game.GetCharacterListRes> EndGetCharacterListRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.GetCharacterListRes>(o);
  }
}


static public class GetCharacterListResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyVectorOfData(tablePos, 6 /*Characters*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}