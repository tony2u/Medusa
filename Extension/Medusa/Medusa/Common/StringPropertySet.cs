using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Medusa.Common
{
    public class StringPropertySet : Dictionary<string, string>
    {
        public void Parse(string val)
        {
            var options = val.Split(new[] { "," }, StringSplitOptions.RemoveEmptyEntries);
            foreach (var option in options)
            {
                var keyValue = option.Split(new[] { "=" }, StringSplitOptions.RemoveEmptyEntries);
                if (keyValue.Length == 2)
                {
                    Add(keyValue[0], keyValue[1]);
                }
                else if (keyValue.Length == 1)
                {
                    Add(keyValue[0], string.Empty);
                }
                else
                {
                    throw new ArgumentException("Invalid attribute str", val);
                }

            }
        }

        public void Set(string name, string val)
        {
            if (ContainsKey(name))
            {
                this[name] = val;
            }
            else
            {
                Add(name, val);
            }
        }
    }
}
