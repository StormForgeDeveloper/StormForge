// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct TransactionID : IFlatbufferObject
{
  private Struct __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public void __init(int _i, ByteBuffer _bb) { __p = new Struct(_i, _bb); }
  public TransactionID __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong TransactionId { get { return __p.bb.GetUlong(__p.bb_pos + 0); } }

  public static Offset<SF.Flat.TransactionID> CreateTransactionID(FlatBufferBuilder builder, ulong TransactionId) {
    builder.Prep(8, 8);
    builder.PutUlong(TransactionId);
    return new Offset<SF.Flat.TransactionID>(builder.Offset);
  }
}


}
