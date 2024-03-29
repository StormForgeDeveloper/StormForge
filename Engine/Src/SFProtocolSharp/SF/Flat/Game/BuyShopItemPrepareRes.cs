// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct BuyShopItemPrepareRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static BuyShopItemPrepareRes GetRootAsBuyShopItemPrepareRes(ByteBuffer _bb) { return GetRootAsBuyShopItemPrepareRes(_bb, new BuyShopItemPrepareRes()); }
  public static BuyShopItemPrepareRes GetRootAsBuyShopItemPrepareRes(ByteBuffer _bb, BuyShopItemPrepareRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public BuyShopItemPrepareRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint ShopItemId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public string PurchaseId { get { int o = __p.__offset(6); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetPurchaseIdBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetPurchaseIdBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetPurchaseIdArray() { return __p.__vector_as_array<byte>(6); }

  public static Offset<SF.Flat.Game.BuyShopItemPrepareRes> CreateBuyShopItemPrepareRes(FlatBufferBuilder builder,
      uint shop_item_id = 0,
      StringOffset purchase_idOffset = default(StringOffset)) {
    builder.StartTable(2);
    BuyShopItemPrepareRes.AddPurchaseId(builder, purchase_idOffset);
    BuyShopItemPrepareRes.AddShopItemId(builder, shop_item_id);
    return BuyShopItemPrepareRes.EndBuyShopItemPrepareRes(builder);
  }

  public static void StartBuyShopItemPrepareRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddShopItemId(FlatBufferBuilder builder, uint shopItemId) { builder.AddUint(0, shopItemId, 0); }
  public static void AddPurchaseId(FlatBufferBuilder builder, StringOffset purchaseIdOffset) { builder.AddOffset(1, purchaseIdOffset.Value, 0); }
  public static Offset<SF.Flat.Game.BuyShopItemPrepareRes> EndBuyShopItemPrepareRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.BuyShopItemPrepareRes>(o);
  }
}


static public class BuyShopItemPrepareResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*ShopItemId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyString(tablePos, 6 /*PurchaseId*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
