// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Siren.Attribute;

namespace Siren
{
    public static class SirenFactory
    {
        public static Dictionary<Type, SirenClass> AllSirenClasses = new Dictionary<Type, SirenClass>();
        public static Dictionary<Type, SirenClass> SirenClasses = new Dictionary<Type, SirenClass>();
        public static Dictionary<Type, SirenClass> GenerictSirenClasses = new Dictionary<Type, SirenClass>();
        public static Dictionary<Type, string> TypeNames = new Dictionary<Type, string>();

        private static bool GetAllDependenciesRecursive(AssemblyName assemblyName, Dictionary<string, AssemblyName> existingRefList)
        {
            var assembly = Assembly.Load(assemblyName);
            var attr = assembly.GetCustomAttribute<SirenAssemblyAttribute>();
            if (attr == null)
            {
                return false;
            }
            List<AssemblyName> a = assembly.GetReferencedAssemblies().ToList();
            foreach (var refAssemblyName in a)
            {
                if (!existingRefList.ContainsKey(refAssemblyName.FullName))
                {
                    if (GetAllDependenciesRecursive(refAssemblyName, existingRefList))
                    {
                        existingRefList.Add(refAssemblyName.FullName, refAssemblyName);
                    }
                }
            }

            return true;
        }

        private static Dictionary<string, AssemblyName> GetAllAssemblies()
        {
            Dictionary<string, AssemblyName> result = new Dictionary<string, AssemblyName>();
            var assemblies = AppDomain.CurrentDomain.GetAssemblies();
            foreach (var assembly in assemblies)
            {
                var attr = assembly.GetCustomAttribute<SirenAssemblyAttribute>();
                if (attr == null)
                {
                    continue;
                }
                if (!result.ContainsKey(assembly.FullName))
                {
                    result.Add(assembly.FullName, assembly.GetName());
                    GetAllDependenciesRecursive(assembly.GetName(), result);
                }
            }

            return result;
        }


        static SirenFactory()
        {
            //register types
            var allAssemblies = GetAllAssemblies();
            foreach (var assemblyName in allAssemblies)
            {
                var assembly = Assembly.Load(assemblyName.Value);
                var types = assembly.GetTypes();
                foreach (var type in types)
                {
                    var attr2 = type.GetCustomAttribute<SirenClassAttribute>();
                    if (attr2 == null)
                    {
                        continue;
                    }


                    SirenClass sirenClass = new SirenClass(type, attr2);
                    AllSirenClasses.Add(type, sirenClass);
                }

                
            }

            foreach (var sirenClass in AllSirenClasses)
            {
                sirenClass.Value.Initialzie();
            }
            

            //only generate current assembly types
            var assemblies = AppDomain.CurrentDomain.GetAssemblies();
            foreach (var assembly in assemblies)
            {
                var attr = assembly.GetCustomAttribute<SirenAssemblyAttribute>();
                if (attr == null)
                {
                    continue;
                }
                if (assembly!=Assembly.GetEntryAssembly())
                {
                    continue;
                }

                var types = assembly.GetTypes();
                foreach (var type in types)
                {
                    var attr2 = type.GetCustomAttribute<SirenClassAttribute>();
                    if (attr2 == null)
                    {
                        continue;
                    }


                    SirenClass sirenClass = new SirenClass(type, attr2);
                    SirenClasses.Add(type, sirenClass);
                }

            }

            List<SirenClass> invalidTypes = new List<SirenClass>();

            foreach (var sirenClass in SirenClasses)
            {
                if (!sirenClass.Value.Initialzie())
                {
                    invalidTypes.Add(sirenClass.Value);
                }
            }

            foreach (var invalidType in invalidTypes)
            {
                SirenClasses.Remove(invalidType.Type);
            }

            foreach (var generictSirenClass in GenerictSirenClasses)
            {
                SirenClasses.Add(generictSirenClass.Key, generictSirenClass.Value);
            }
            GenerictSirenClasses.Clear();
        }

        public static SirenClass FindClass(Type type)
        {
            if (type.IsPrimitive || type == typeof(string) || type == typeof(byte[]))
            {
                return null;
            }

            SirenClass sirenClass;
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
                        testType = oldType.MakeGenericType(type.GenericTypeArguments);
                        if (testType == type)
                        {

                            var attr2 = type.GetCustomAttribute<SirenClassAttribute>();
                            if (attr2 == null)
                            {
                                return null;
                            }


                            sirenClass = new SirenClass(type, attr2);
                            sirenClass.Initialzie();
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

        public static SirenDataType GetDataType(Type type)
        {
            if (type.IsGenericType)
            {
                if (type.Name.StartsWith("List"))
                {
                    return SirenDataType.List;
                }
                if (type.Name.StartsWith("Dictionary"))
                {
                    return SirenDataType.Dictionary;
                }
            }
            else
            {
                if (type.IsValueType)
                {
                    if (type == typeof(string))
                    {
                        return SirenDataType.String;
                    }
                    if (type == typeof(byte[]))
                    {
                        return SirenDataType.Blob;
                    }

                    if (type == typeof(bool))
                    {
                        return SirenDataType.Bool;
                    }
                    if (type == typeof(char))
                    {
                        return SirenDataType.Int8;
                    }
                    if (type == typeof(short))
                    {
                        return SirenDataType.Int16;
                    }
                    if (type == typeof(int))
                    {
                        return SirenDataType.Int32;
                    }
                    if (type == typeof(Int64))
                    {
                        return SirenDataType.Int64;
                    }
                    if (type == typeof(byte))
                    {
                        return SirenDataType.UInt8;
                    }
                    if (type == typeof(ushort))
                    {
                        return SirenDataType.UInt16;
                    }
                    if (type == typeof(uint))
                    {
                        return SirenDataType.UInt32;
                    }
                    if (type == typeof(UInt64))
                    {
                        return SirenDataType.UInt64;
                    }
                    if (type == typeof(float))
                    {
                        return SirenDataType.Float;
                    }
                    if (type == typeof(double))
                    {
                        return SirenDataType.Double;
                    }

                }

            }
            return SirenDataType.Struct;

        }

        public static void RegisterTypeName<T>(string name)
        {
            var type = typeof(T);
            if (!TypeNames.ContainsKey(type))
            {
                TypeNames.Add(type, name);
            }
        }

        public static string GetTypeName(Type type, bool forceToPtr = false)
        {
            string outStr;
            if (TypeNames.TryGetValue(type, out outStr))
            {
                return outStr;
            }
            if (type == typeof(bool))
            {
                return "bool";
            }
            if (type == typeof(string))
            {
                return "HeapString";
            }
            if (type == typeof(byte[]))
            {
                return "MemoryByteData";
            }
            if (type == typeof(char))
            {
                return "char";
            }
            if (type == typeof(short))
            {
                return "short";
            }
            if (type == typeof(int))
            {
                return "int";
            }
            if (type == typeof(Int64))
            {
                return "int64";
            }
            if (type == typeof(byte))
            {
                return "byte";
            }
            if (type == typeof(ushort))
            {
                return "ushort";
            }
            if (type == typeof(uint))
            {
                return "uint";
            }
            if (type == typeof(UInt64))
            {
                return "uint64";
            }
            if (type == typeof(float))
            {
                return "float";
            }
            if (type == typeof(double))
            {
                return "double";
            }

            var str = type.Name;
            int index = str.LastIndexOf('.');
            if (index > 0)
            {
                str = str.Remove(0, index + 1);
            }

            if (forceToPtr)
            {
                return str + "*";
            }

            return str;
        }
    }
}
