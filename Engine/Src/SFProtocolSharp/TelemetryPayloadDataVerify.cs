
namespace SF.Flat.Telemetry
{
    static public class PayloadDataVerify
    {
        static public bool Verify(Google.FlatBuffers.Verifier verifier, byte typeId, uint tablePos)
        {
            return true;
        }
    }

    static public class EventAttributeValueVerify
    {
        static public bool Verify(Google.FlatBuffers.Verifier verifier, byte typeId, uint tablePos)
        {
            return true;
        }
    }

}
