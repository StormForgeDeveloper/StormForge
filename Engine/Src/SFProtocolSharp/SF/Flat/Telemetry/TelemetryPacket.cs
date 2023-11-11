// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Telemetry
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct TelemetryPacket : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static TelemetryPacket GetRootAsTelemetryPacket(ByteBuffer _bb) { return GetRootAsTelemetryPacket(_bb, new TelemetryPacket()); }
  public static TelemetryPacket GetRootAsTelemetryPacket(ByteBuffer _bb, TelemetryPacket obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public static bool VerifyTelemetryPacket(ByteBuffer _bb) {Google.FlatBuffers.Verifier verifier = new Google.FlatBuffers.Verifier(_bb); return verifier.VerifyBuffer("", false, TelemetryPacketVerify.Verify); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public TelemetryPacket __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint RequestId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public SF.Flat.Telemetry.PayloadData PayloadDataType { get { int o = __p.__offset(6); return o != 0 ? (SF.Flat.Telemetry.PayloadData)__p.bb.Get(o + __p.bb_pos) : SF.Flat.Telemetry.PayloadData.NONE; } }
  public TTable? PayloadData<TTable>() where TTable : struct, IFlatbufferObject { int o = __p.__offset(8); return o != 0 ? (TTable?)__p.__union<TTable>(o + __p.bb_pos) : null; }
  public SF.Flat.Telemetry.GenericError PayloadDataAsGenericError() { return PayloadData<SF.Flat.Telemetry.GenericError>().Value; }
  public SF.Flat.Telemetry.PostEventRequest PayloadDataAsPostEventRequest() { return PayloadData<SF.Flat.Telemetry.PostEventRequest>().Value; }
  public SF.Flat.Telemetry.PostEventResult PayloadDataAsPostEventResult() { return PayloadData<SF.Flat.Telemetry.PostEventResult>().Value; }

  public static Offset<SF.Flat.Telemetry.TelemetryPacket> CreateTelemetryPacket(FlatBufferBuilder builder,
      uint request_id = 0,
      SF.Flat.Telemetry.PayloadData payload_data_type = SF.Flat.Telemetry.PayloadData.NONE,
      int payload_dataOffset = 0) {
    builder.StartTable(3);
    TelemetryPacket.AddPayloadData(builder, payload_dataOffset);
    TelemetryPacket.AddRequestId(builder, request_id);
    TelemetryPacket.AddPayloadDataType(builder, payload_data_type);
    return TelemetryPacket.EndTelemetryPacket(builder);
  }

  public static void StartTelemetryPacket(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddRequestId(FlatBufferBuilder builder, uint requestId) { builder.AddUint(0, requestId, 0); }
  public static void AddPayloadDataType(FlatBufferBuilder builder, SF.Flat.Telemetry.PayloadData payloadDataType) { builder.AddByte(1, (byte)payloadDataType, 0); }
  public static void AddPayloadData(FlatBufferBuilder builder, int payloadDataOffset) { builder.AddOffset(2, payloadDataOffset, 0); }
  public static Offset<SF.Flat.Telemetry.TelemetryPacket> EndTelemetryPacket(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Telemetry.TelemetryPacket>(o);
  }
  public static void FinishTelemetryPacketBuffer(FlatBufferBuilder builder, Offset<SF.Flat.Telemetry.TelemetryPacket> offset) { builder.Finish(offset.Value); }
  public static void FinishSizePrefixedTelemetryPacketBuffer(FlatBufferBuilder builder, Offset<SF.Flat.Telemetry.TelemetryPacket> offset) { builder.FinishSizePrefixed(offset.Value); }
}


static public class TelemetryPacketVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*RequestId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*PayloadDataType*/, 1 /*SF.Flat.Telemetry.PayloadData*/, 1, false)
      && verifier.VerifyUnion(tablePos, 6, 8 /*PayloadData*/, SF.Flat.Telemetry.PayloadDataVerify.Verify, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}