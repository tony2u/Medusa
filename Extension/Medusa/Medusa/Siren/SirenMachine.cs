using System;
using System.Collections.Generic;
using System.Reflection;
using Medusa.Log;
using Medusa.Siren.Schema;

namespace Medusa.Siren
{
    public static class SirenMachine
    {
        public static readonly SirenBuildinBool Bool = new SirenBuildinBool("bool");
        public static readonly SirenBuildinInt8 Int8 = new SirenBuildinInt8("char");
        public static readonly SirenBuildinUInt8 UInt8 = new SirenBuildinUInt8("byte");
        public static readonly SirenBuildinInt16 Int16 = new SirenBuildinInt16("short");
        public static readonly SirenBuildinUInt16 UInt16 = new SirenBuildinUInt16("ushort");
        public static readonly SirenBuildinInt32 Int32 = new SirenBuildinInt32("int");
        public static readonly SirenBuildinUInt32 UInt32 = new SirenBuildinUInt32("uint");
        public static readonly SirenBuildinInt64 Int64 = new SirenBuildinInt64("int64");
        public static readonly SirenBuildinUInt64 UInt64 = new SirenBuildinUInt64("uint64");
        public static readonly SirenBuildinFloat Float = new SirenBuildinFloat("float");
        public static readonly SirenBuildinDouble Double = new SirenBuildinDouble("double");
        public static readonly SirenBuildinString String = new SirenBuildinString("HeapString");
        public static readonly SirenBuildinBlob Blob = new SirenBuildinBlob("MemoryData");
        public static readonly SirenBuildinList List = new SirenBuildinList("List");
        public static readonly SirenBuildinDictionary Dictionary = new SirenBuildinDictionary("Dictionary");

        public static readonly Dictionary<string, SirenBuildinType> BuildinTypes = new Dictionary<string, SirenBuildinType>();
        public static readonly Dictionary<string, SirenAssembly> Assemblies = new Dictionary<string, SirenAssembly>();

        public static Dictionary<Type, SirenCustomClass> AllSirenClasses = new Dictionary<Type, SirenCustomClass>();
        public static Dictionary<Type, SirenCustomEnum> AllSirenEnums = new Dictionary<Type, SirenCustomEnum>();
        public static Dictionary<Type, SirenCustomClass> GenerictSirenClasses = new Dictionary<Type, SirenCustomClass>();

        static SirenMachine()
        {
            BuildinTypes.Add(Bool.Name, Bool);
            BuildinTypes.Add(Int8.Name, Int8);
            BuildinTypes.Add(UInt8.Name, UInt8);
            BuildinTypes.Add(Int16.Name, Int16);
            BuildinTypes.Add(UInt16.Name, UInt16);
            BuildinTypes.Add(Int32.Name, Int32);
            BuildinTypes.Add(UInt32.Name, UInt32);
            BuildinTypes.Add(Int64.Name, Int64);
            BuildinTypes.Add(UInt64.Name, UInt64);
            BuildinTypes.Add(Float.Name, Float);
            BuildinTypes.Add(Double.Name, Double);
            BuildinTypes.Add(String.Name, String);
            BuildinTypes.Add(Blob.Name, Blob);
            BuildinTypes.Add(List.Name, List);
            BuildinTypes.Add(Dictionary.Name, Dictionary);

            //alias
            BuildinTypes.Add("int8", Int8);
            BuildinTypes.Add("uint8", UInt8);
            BuildinTypes.Add("int16", Int16);
            BuildinTypes.Add("uint16", UInt16);
            BuildinTypes.Add("int32", Int32);
            BuildinTypes.Add("uint32", UInt32);
            BuildinTypes.Add("long", Int64);
            BuildinTypes.Add("ulong", UInt64);
            BuildinTypes.Add("string", String);
            BuildinTypes.Add("String", String);
            BuildinTypes.Add("blob", Blob);

            //register types
            var allAssemblies = GetAllAssemblies();
            foreach (var assemblyName in allAssemblies)
            {
                var assembly = Assembly.Load(assemblyName.Value);
                var types = assembly.GetTypes();
                foreach (var type in types)
                {
                    var attr2 = type.GetCustomAttributes(typeof(SirenClassAttribute), false);
                    if (attr2.Length > 0)
                    {
                        SirenCustomClass sirenClass = new SirenCustomClass(type, attr2[0] as SirenClassAttribute);
                        AllSirenClasses.Add(type, sirenClass);
                    }

                    var attr3 = type.GetCustomAttributes(typeof(SirenEnumAttribute), false);
                    if (attr3.Length > 0)
                    {
                        SirenCustomEnum sirenEnum = new SirenCustomEnum(type, attr3[0] as SirenEnumAttribute);
                        AllSirenEnums.Add(type, sirenEnum);
                    }
                }
            }

            foreach (var sirenClass in AllSirenClasses)
            {
                sirenClass.Value.Initialize();
            }

            foreach (var sirenClass in AllSirenEnums)
            {
                sirenClass.Value.Initialize();
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

        public static SirenCustomClass GetClass(Type type)
        {
            var classType = FindClass(type);
            if (classType == null)
            {
                Logger.ErrorLine("Cannot find type:{0}", type);
            }
            return classType;
        }

        public static SirenCustomClass FindClass(Type type)
        {
            if (type.IsPrimitive || type == typeof(string) || type == typeof(byte[]))
            {
                return null;
            }

            SirenCustomClass sirenClass;
            if (AllSirenClasses.TryGetValue(type, out sirenClass)) return sirenClass;

            if (GenerictSirenClasses.TryGetValue(type, out sirenClass))
            {
                return sirenClass;
            }

            if (type.IsGenericType)
            {
                Type testType = null;
                foreach (var temp in AllSirenClasses)
                {
                    var oldType = temp.Key;
                    if (oldType.IsGenericTypeDefinition)
                    {
                        testType = oldType.MakeGenericType(type.GetGenericArguments());
                        if (testType == type)
                        {

                            var attr2 = type.GetCustomAttributes(typeof(SirenClassAttribute), false);
                            if (attr2.Length <= 0)
                            {
                                return null;
                            }


                            sirenClass = new SirenCustomClass(type, attr2[0] as SirenClassAttribute);
                            sirenClass.Initialize();
                            break;
                        }
                        testType = null;

                    }
                }

                if (testType != null)
                {
                    GenerictSirenClasses.Add(testType, sirenClass);
                }

            }

            return sirenClass;

        }

        public static object Create(Type type)
        {
            return Activator.CreateInstance(type);
        }

        public static SirenType GetType(Type type)
        {
            var classType = FindType(type);
            if (classType == null)
            {
                Logger.ErrorLine("Cannot find type:{0}", type);
            }
            return classType;
        }


        public static SirenType FindType(Type type)
        {
            if (type.IsGenericType)
            {
                if (type.Name.StartsWith("List"))
                {
                    return new SirenBuildinList(type);
                }
                if (type.Name.StartsWith("Dictionary"))
                {
                    return new SirenBuildinDictionary(type);
                }
            }
            else
            {
                if (type.IsValueType)
                {

                    if (type == typeof(bool))
                    {
                        return Bool;
                    }
                    if (type == typeof(char))
                    {
                        return Int8;
                    }
                    if (type == typeof(short))
                    {
                        return Int16;
                    }
                    if (type == typeof(int))
                    {
                        return Int32;
                    }
                    if (type == typeof(Int64))
                    {
                        return Int64;
                    }
                    if (type == typeof(byte))
                    {
                        return UInt8;
                    }
                    if (type == typeof(ushort))
                    {
                        return UInt16;
                    }
                    if (type == typeof(uint))
                    {
                        return UInt32;
                    }
                    if (type == typeof(UInt64))
                    {
                        return UInt64;
                    }
                    if (type == typeof(float))
                    {
                        return Float;
                    }
                    if (type == typeof(double))
                    {
                        return Double;
                    }

                }
                else
                {
                    if (type == typeof(string))
                    {
                        return String;
                    }
                    if (type == typeof(byte[]))
                    {
                        return Blob;
                    }

                }

            }


            SirenCustomClass sirenClass;
            if (AllSirenClasses.TryGetValue(type, out sirenClass)) return sirenClass;

            if (GenerictSirenClasses.TryGetValue(type, out sirenClass))
            {
                return sirenClass;
            }

            SirenCustomEnum sirenEnum;
            if (AllSirenEnums.TryGetValue(type, out sirenEnum)) return sirenEnum;

            if (type.IsGenericType)
            {
                Type testType = null;
                foreach (var temp in AllSirenClasses)
                {
                    var oldType = temp.Key;
                    if (oldType.IsGenericTypeDefinition)
                    {
                        testType = oldType.MakeGenericType(type.GetGenericArguments());
                        if (testType == type)
                        {

                            var attr2 = type.GetCustomAttributes(typeof(SirenClassAttribute), false);
                            if (attr2.Length <= 0)
                            {
                                return null;
                            }


                            sirenClass = new SirenCustomClass(type, attr2[0] as SirenClassAttribute);
                            sirenClass.Initialize();
                            break;
                        }
                        testType = null;

                    }
                }

                if (testType != null)
                {
                    GenerictSirenClasses.Add(testType, sirenClass);
                }

            }

            return sirenClass;

        }


        public static SirenTypeId GetTypeId(Type type)
        {
            if (type.IsGenericType)
            {
                if (type.Name.StartsWith("List"))
                {
                    return SirenTypeId.List;
                }
                if (type.Name.StartsWith("Dictionary"))
                {
                    return SirenTypeId.Dictionary;
                }
            }
            else
            {
                if (type.IsValueType)
                {


                    if (type == typeof(bool))
                    {
                        return SirenTypeId.Bool;
                    }
                    if (type == typeof(char))
                    {
                        return SirenTypeId.Int8;
                    }
                    if (type == typeof(short))
                    {
                        return SirenTypeId.Int16;
                    }
                    if (type == typeof(int))
                    {
                        return SirenTypeId.Int32;
                    }
                    if (type == typeof(Int64))
                    {
                        return SirenTypeId.Int64;
                    }
                    if (type == typeof(byte))
                    {
                        return SirenTypeId.UInt8;
                    }
                    if (type == typeof(ushort))
                    {
                        return SirenTypeId.UInt16;
                    }
                    if (type == typeof(uint))
                    {
                        return SirenTypeId.UInt32;
                    }
                    if (type == typeof(UInt64))
                    {
                        return SirenTypeId.UInt64;
                    }
                    if (type == typeof(float))
                    {
                        return SirenTypeId.Float;
                    }
                    if (type == typeof(double))
                    {
                        return SirenTypeId.Double;
                    }
                    if (type.IsEnum)
                    {
                        return SirenTypeId.Enum;
                    }
                }
                else
                {
                    if (type == typeof(string))
                    {
                        return SirenTypeId.String;
                    }
                    if (type == typeof(byte[]))
                    {
                        return SirenTypeId.Blob;
                    }
                }

            }
            return SirenTypeId.Struct;

        }

    }
}
