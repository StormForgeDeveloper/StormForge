// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Telemetry
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct PostEventResult : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static PostEventResult GetRootAsPostEventResult(ByteBuffer _bb) { return GetRootAsPostEventResult(_bb, new PostEventResult()); }
  public static PostEventResult GetRootAsPostEventResult(ByteBuffer _bb, PostEventResult obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public PostEventResult __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }


  public static void StartPostEventResult(FlatBufferBuilder builder) { builder.StartTable(0); }
  public static Offset<SF.Flat.Telemetry.PostEventResult> EndPostEventResult(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Telemetry.PostEventResult>(o);
  }
}


static public class PostEventResultVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
