// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct GetFriendListRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static GetFriendListRes GetRootAsGetFriendListRes(ByteBuffer _bb) { return GetRootAsGetFriendListRes(_bb, new GetFriendListRes()); }
  public static GetFriendListRes GetRootAsGetFriendListRes(ByteBuffer _bb, GetFriendListRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public GetFriendListRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public ushort MaxFriendSlot { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUshort(o + __p.bb_pos) : (ushort)0; } }
  public ushort TotalNumberOfFriends { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetUshort(o + __p.bb_pos) : (ushort)0; } }
  public ushort StartIndex { get { int o = __p.__offset(10); return o != 0 ? __p.bb.GetUshort(o + __p.bb_pos) : (ushort)0; } }
  public SF.Flat.PlayerInformation? FriendList(int j) { int o = __p.__offset(12); return o != 0 ? (SF.Flat.PlayerInformation?)(new SF.Flat.PlayerInformation()).__assign(__p.__indirect(__p.__vector(o) + j * 4), __p.bb) : null; }
  public int FriendListLength { get { int o = __p.__offset(12); return o != 0 ? __p.__vector_len(o) : 0; } }

  public static Offset<SF.Flat.Game.GetFriendListRes> CreateGetFriendListRes(FlatBufferBuilder builder,
      uint result = 0,
      ushort max_friend_slot = 0,
      ushort total_number_of_friends = 0,
      ushort start_index = 0,
      VectorOffset friend_listOffset = default(VectorOffset)) {
    builder.StartTable(5);
    GetFriendListRes.AddFriendList(builder, friend_listOffset);
    GetFriendListRes.AddResult(builder, result);
    GetFriendListRes.AddStartIndex(builder, start_index);
    GetFriendListRes.AddTotalNumberOfFriends(builder, total_number_of_friends);
    GetFriendListRes.AddMaxFriendSlot(builder, max_friend_slot);
    return GetFriendListRes.EndGetFriendListRes(builder);
  }

  public static void StartGetFriendListRes(FlatBufferBuilder builder) { builder.StartTable(5); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static void AddMaxFriendSlot(FlatBufferBuilder builder, ushort maxFriendSlot) { builder.AddUshort(1, maxFriendSlot, 0); }
  public static void AddTotalNumberOfFriends(FlatBufferBuilder builder, ushort totalNumberOfFriends) { builder.AddUshort(2, totalNumberOfFriends, 0); }
  public static void AddStartIndex(FlatBufferBuilder builder, ushort startIndex) { builder.AddUshort(3, startIndex, 0); }
  public static void AddFriendList(FlatBufferBuilder builder, VectorOffset friendListOffset) { builder.AddOffset(4, friendListOffset.Value, 0); }
  public static VectorOffset CreateFriendListVector(FlatBufferBuilder builder, Offset<SF.Flat.PlayerInformation>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static VectorOffset CreateFriendListVectorBlock(FlatBufferBuilder builder, Offset<SF.Flat.PlayerInformation>[] data) { builder.StartVector(4, data.Length, 4); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateFriendListVectorBlock(FlatBufferBuilder builder, ArraySegment<Offset<SF.Flat.PlayerInformation>> data) { builder.StartVector(4, data.Count, 4); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateFriendListVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<Offset<SF.Flat.PlayerInformation>>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartFriendListVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<SF.Flat.Game.GetFriendListRes> EndGetFriendListRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.GetFriendListRes>(o);
  }
}


static public class GetFriendListResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*MaxFriendSlot*/, 2 /*ushort*/, 2, false)
      && verifier.VerifyField(tablePos, 8 /*TotalNumberOfFriends*/, 2 /*ushort*/, 2, false)
      && verifier.VerifyField(tablePos, 10 /*StartIndex*/, 2 /*ushort*/, 2, false)
      && verifier.VerifyVectorOfTables(tablePos, 12 /*FriendList*/, SF.Flat.PlayerInformationVerify.Verify, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}