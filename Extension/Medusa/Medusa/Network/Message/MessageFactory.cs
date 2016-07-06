using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Medusa.Log;
using Medusa.Siren.Schema;

namespace Medusa.Network.Message
{
    public static class MessageFactory
    {
        private static readonly Dictionary<uint, Type> mMessages = new Dictionary<uint, Type>();
        public static uint SessionId = 0;

        public static void RegisterAll()
        {
            Register(0, typeof(HeartbeatMessage));
        }

        public static bool IsSubclassOfRecursively(this Type type, Type other)
        {
            if (type.IsSubclassOf(other))
            {
                return true;
            }
            if (type.BaseType == null)
            {
                return false;
            }
            return IsSubclassOfRecursively(type.BaseType, other);
        }
        static MessageFactory()
        {
            //register types
            var allAssemblies = GetAllAssemblies();
            foreach (var assemblyName in allAssemblies)
            {
                var assembly = Assembly.Load(assemblyName.Value);
                var types = assembly.GetTypes();
                foreach (var type in types)
                {
                    if (type.IsSubclassOf(typeof(BaseMessage)) && !type.IsAbstract && !type.IsGenericType)
                    {
                        var requestProperty = type.GetProperty("Request");

                        var attr2 = requestProperty.PropertyType.GetCustomAttributes(typeof(SirenClassAttribute), false);
                        if (attr2.Length > 0)
                        {
                            var idAttr = attr2[0] as SirenClassAttribute;
                            if (idAttr != null && idAttr.KeyValues.ContainsKey("Id"))
                            {
                                var idStr = idAttr.KeyValues["Id"];
                                uint id = Convert.ToUInt32(idStr);
                                Register(id, type);
                            }
                            else
                            {
                                Logger.ErrorLine("Cannot find siren class attribute on type:{0}", type);
                            }
                        }

                    }

                }
            }

        }

        private static Dictionary<string, AssemblyName> GetAllAssemblies()
        {
            Dictionary<string, AssemblyName> result = new Dictionary<string, AssemblyName>();
            var assemblies = AppDomain.CurrentDomain.GetAssemblies();
            foreach (var assembly in assemblies)
            {
                var attr = assembly.GetCustomAttributes(typeof(SirenAssemblyAttribute), false);
                if (attr.Length <= 0)
                {
                    continue;
                }
                if (!result.ContainsKey(assembly.FullName))
                {
                    result.Add(assembly.FullName, assembly.GetName());
                }
            }

            return result;
        }

        public static void Register(uint id, Type type)
        {
            if (mMessages.ContainsKey(id))
            {
                var prev = mMessages[id];
                throw new Exception(string.Format("Duplicate message id:{0} of {1}. Prev is {2}", id, type, prev));
            }
            mMessages.Add(id, type);
        }

        public static IMessage Create(uint id)
        {
            Type outType;
            if (mMessages.TryGetValue(id, out outType))
            {
                return Activator.CreateInstance(outType) as IMessage;
            }
            Logger.ErrorLine("Cannot create message with id:{0}", id);
            return null;
        }
    }
}