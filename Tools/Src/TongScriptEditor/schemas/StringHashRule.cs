
using Sce.Atf.Dom;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VisualScript
{
    public class StringHashRule : AttributeRule
    {
        public enum HashType
        {
            CRC32,
            HASH64, // WWE uses MURMUR64
        }

        public HashType Hash
        {
            get; set;
        }

        public StringHashRule(HashType hash = HashType.HASH64)
        {
            Hash = hash;
        }


        public override bool Validate(object value, AttributeInfo info)
        {
            if(value.GetType() != typeof(string))
                throw new InvalidOperationException("Invalid attribute type rule");

            return true;
        }
    }
}
