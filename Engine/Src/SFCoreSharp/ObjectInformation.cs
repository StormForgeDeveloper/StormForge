////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
// Description : Object Information
//	
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

#nullable enable

namespace SF
{
    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public class ObjectInformation
    {
        public Guid SignatureID { get; set; } = Guid.Empty;
        public ulong UID { get; set; } = 0;
        public string Name { get; set; } = string.Empty;
        public System.TimeSpan? Lifetime { get; set; } = null;
        public DateTime Created { get; set; } = DateTime.UtcNow;
        public DateTime Updated { get; set; } = DateTime.UtcNow;
        public byte[]? CustomData { get; set; } = null;

        // Directory Path
        public string[] DirectoryPaths = new string[0];
        // Object UID node for id reference tracking
        public LinkedListNode<ulong>? ObjectUIDNode = null;

        public bool HasExpired => Lifetime != null && (DateTime.UtcNow - Updated) > Lifetime;
    }



}

#nullable restore
