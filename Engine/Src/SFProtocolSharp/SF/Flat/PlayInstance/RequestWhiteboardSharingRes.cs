// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct RequestWhiteboardSharingRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static RequestWhiteboardSharingRes GetRootAsRequestWhiteboardSharingRes(ByteBuffer _bb) { return GetRootAsRequestWhiteboardSharingRes(_bb, new RequestWhiteboardSharingRes()); }
  public static RequestWhiteboardSharingRes GetRootAsRequestWhiteboardSharingRes(ByteBuffer _bb, RequestWhiteboardSharingRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public RequestWhiteboardSharingRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.PlayInstance.RequestWhiteboardSharingRes> CreateRequestWhiteboardSharingRes(FlatBufferBuilder builder,
      uint result = 0) {
    builder.StartTable(1);
    RequestWhiteboardSharingRes.AddResult(builder, result);
    return RequestWhiteboardSharingRes.EndRequestWhiteboardSharingRes(builder);
  }

  public static void StartRequestWhiteboardSharingRes(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static Offset<SF.Flat.PlayInstance.RequestWhiteboardSharingRes> EndRequestWhiteboardSharingRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.RequestWhiteboardSharingRes>(o);
  }
}


static public class RequestWhiteboardSharingResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
