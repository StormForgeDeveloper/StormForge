// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Telemetry
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct PostEventRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static PostEventRes GetRootAsPostEventRes(ByteBuffer _bb) { return GetRootAsPostEventRes(_bb, new PostEventRes()); }
  public static PostEventRes GetRootAsPostEventRes(ByteBuffer _bb, PostEventRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public static bool VerifyPostEventRes(ByteBuffer _bb) {Google.FlatBuffers.Verifier verifier = new Google.FlatBuffers.Verifier(_bb); return verifier.VerifyBuffer("", false, PostEventResVerify.Verify); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public PostEventRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }


  public static void StartPostEventRes(FlatBufferBuilder builder) { builder.StartTable(0); }
  public static Offset<SF.Flat.Telemetry.PostEventRes> EndPostEventRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Telemetry.PostEventRes>(o);
  }
  public static void FinishPostEventResBuffer(FlatBufferBuilder builder, Offset<SF.Flat.Telemetry.PostEventRes> offset) { builder.Finish(offset.Value); }
  public static void FinishSizePrefixedPostEventResBuffer(FlatBufferBuilder builder, Offset<SF.Flat.Telemetry.PostEventRes> offset) { builder.FinishSizePrefixed(offset.Value); }
}


static public class PostEventResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
