// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct BuyShopItemPrepareCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static BuyShopItemPrepareCmd GetRootAsBuyShopItemPrepareCmd(ByteBuffer _bb) { return GetRootAsBuyShopItemPrepareCmd(_bb, new BuyShopItemPrepareCmd()); }
  public static BuyShopItemPrepareCmd GetRootAsBuyShopItemPrepareCmd(ByteBuffer _bb, BuyShopItemPrepareCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public BuyShopItemPrepareCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint ShopItemId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.Game.BuyShopItemPrepareCmd> CreateBuyShopItemPrepareCmd(FlatBufferBuilder builder,
      uint shop_item_id = 0) {
    builder.StartTable(1);
    BuyShopItemPrepareCmd.AddShopItemId(builder, shop_item_id);
    return BuyShopItemPrepareCmd.EndBuyShopItemPrepareCmd(builder);
  }

  public static void StartBuyShopItemPrepareCmd(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddShopItemId(FlatBufferBuilder builder, uint shopItemId) { builder.AddUint(0, shopItemId, 0); }
  public static Offset<SF.Flat.Game.BuyShopItemPrepareCmd> EndBuyShopItemPrepareCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.BuyShopItemPrepareCmd>(o);
  }
}


static public class BuyShopItemPrepareCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*ShopItemId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
