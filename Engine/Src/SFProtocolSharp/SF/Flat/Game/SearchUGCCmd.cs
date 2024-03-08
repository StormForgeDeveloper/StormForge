// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct SearchUGCCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static SearchUGCCmd GetRootAsSearchUGCCmd(ByteBuffer _bb) { return GetRootAsSearchUGCCmd(_bb, new SearchUGCCmd()); }
  public static SearchUGCCmd GetRootAsSearchUGCCmd(ByteBuffer _bb, SearchUGCCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public SearchUGCCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public string Tags(int j) { int o = __p.__offset(4); return o != 0 ? __p.__string(__p.__vector(o) + j * 4) : null; }
  public int TagsLength { get { int o = __p.__offset(4); return o != 0 ? __p.__vector_len(o) : 0; } }

  public static Offset<SF.Flat.Game.SearchUGCCmd> CreateSearchUGCCmd(FlatBufferBuilder builder,
      VectorOffset tagsOffset = default(VectorOffset)) {
    builder.StartTable(1);
    SearchUGCCmd.AddTags(builder, tagsOffset);
    return SearchUGCCmd.EndSearchUGCCmd(builder);
  }

  public static void StartSearchUGCCmd(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddTags(FlatBufferBuilder builder, VectorOffset tagsOffset) { builder.AddOffset(0, tagsOffset.Value, 0); }
  public static VectorOffset CreateTagsVector(FlatBufferBuilder builder, StringOffset[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static VectorOffset CreateTagsVectorBlock(FlatBufferBuilder builder, StringOffset[] data) { builder.StartVector(4, data.Length, 4); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateTagsVectorBlock(FlatBufferBuilder builder, ArraySegment<StringOffset> data) { builder.StartVector(4, data.Count, 4); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateTagsVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<StringOffset>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartTagsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<SF.Flat.Game.SearchUGCCmd> EndSearchUGCCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.SearchUGCCmd>(o);
  }
}


static public class SearchUGCCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyVectorOfStrings(tablePos, 4 /*Tags*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
