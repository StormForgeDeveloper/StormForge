// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct CallFunctionCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static CallFunctionCmd GetRootAsCallFunctionCmd(ByteBuffer _bb) { return GetRootAsCallFunctionCmd(_bb, new CallFunctionCmd()); }
  public static CallFunctionCmd GetRootAsCallFunctionCmd(ByteBuffer _bb, CallFunctionCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public CallFunctionCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint FunctionName { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public ulong PlayerId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public byte Parameters(int j) { int o = __p.__offset(8); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int ParametersLength { get { int o = __p.__offset(8); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetParametersBytes() { return __p.__vector_as_span<byte>(8, 1); }
#else
  public ArraySegment<byte>? GetParametersBytes() { return __p.__vector_as_arraysegment(8); }
#endif
  public byte[] GetParametersArray() { return __p.__vector_as_array<byte>(8); }

  public static Offset<SF.Flat.PlayInstance.CallFunctionCmd> CreateCallFunctionCmd(FlatBufferBuilder builder,
      uint function_name = 0,
      ulong player_id = 0,
      VectorOffset parametersOffset = default(VectorOffset)) {
    builder.StartTable(3);
    CallFunctionCmd.AddPlayerId(builder, player_id);
    CallFunctionCmd.AddParameters(builder, parametersOffset);
    CallFunctionCmd.AddFunctionName(builder, function_name);
    return CallFunctionCmd.EndCallFunctionCmd(builder);
  }

  public static void StartCallFunctionCmd(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddFunctionName(FlatBufferBuilder builder, uint functionName) { builder.AddUint(0, functionName, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, ulong playerId) { builder.AddUlong(1, playerId, 0); }
  public static void AddParameters(FlatBufferBuilder builder, VectorOffset parametersOffset) { builder.AddOffset(2, parametersOffset.Value, 0); }
  public static VectorOffset CreateParametersVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateParametersVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateParametersVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateParametersVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartParametersVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.PlayInstance.CallFunctionCmd> EndCallFunctionCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.CallFunctionCmd>(o);
  }
}


static public class CallFunctionCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*FunctionName*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyVectorOfData(tablePos, 8 /*Parameters*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
