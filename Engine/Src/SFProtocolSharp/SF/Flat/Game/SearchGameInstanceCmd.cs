// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct SearchGameInstanceCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static SearchGameInstanceCmd GetRootAsSearchGameInstanceCmd(ByteBuffer _bb) { return GetRootAsSearchGameInstanceCmd(_bb, new SearchGameInstanceCmd()); }
  public static SearchGameInstanceCmd GetRootAsSearchGameInstanceCmd(ByteBuffer _bb, SearchGameInstanceCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public SearchGameInstanceCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public string SearchKeyword { get { int o = __p.__offset(4); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetSearchKeywordBytes() { return __p.__vector_as_span<byte>(4, 1); }
#else
  public ArraySegment<byte>? GetSearchKeywordBytes() { return __p.__vector_as_arraysegment(4); }
#endif
  public byte[] GetSearchKeywordArray() { return __p.__vector_as_array<byte>(4); }
  public uint ZoneTableId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.Game.SearchGameInstanceCmd> CreateSearchGameInstanceCmd(FlatBufferBuilder builder,
      StringOffset search_keywordOffset = default(StringOffset),
      uint zone_table_id = 0) {
    builder.StartTable(2);
    SearchGameInstanceCmd.AddZoneTableId(builder, zone_table_id);
    SearchGameInstanceCmd.AddSearchKeyword(builder, search_keywordOffset);
    return SearchGameInstanceCmd.EndSearchGameInstanceCmd(builder);
  }

  public static void StartSearchGameInstanceCmd(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddSearchKeyword(FlatBufferBuilder builder, StringOffset searchKeywordOffset) { builder.AddOffset(0, searchKeywordOffset.Value, 0); }
  public static void AddZoneTableId(FlatBufferBuilder builder, uint zoneTableId) { builder.AddUint(1, zoneTableId, 0); }
  public static Offset<SF.Flat.Game.SearchGameInstanceCmd> EndSearchGameInstanceCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.SearchGameInstanceCmd>(o);
  }
}


static public class SearchGameInstanceCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyString(tablePos, 4 /*SearchKeyword*/, false)
      && verifier.VerifyField(tablePos, 6 /*ZoneTableId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
