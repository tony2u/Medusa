// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Siren.Attribute;
using Siren.Template;

namespace Siren
{
    public class SirenClass
    {
        public Type Type { get; set; }
        public SirenClassAttribute Attribute { get; set; }
        public HashSet<Type> IncludeTypes { get; private set; }
        public ISirenTemplate Template { get; private set; }
        public List<SirenProperty> Properties = new List<SirenProperty>();
        public SirenClass BaseSirenClass { get; private set; }
        public Dictionary<ushort, SirenProperty> PropertyIdDict = new Dictionary<ushort, SirenProperty>();
        public Dictionary<String, SirenProperty> PropertyNameDict = new Dictionary<String, SirenProperty>();
        public MethodInfo SerializeMethodInfo { get; private set; }
        public MethodInfo DeserializeMethodInfo { get; private set; }
        public MethodInfo RegisterMethodInfo { get; private set; }



        public string Name
        {
            get
            {
                var str = Type.Name;
                if (str.Contains('.'))
                {
                    str = str.Remove(0, str.LastIndexOf('.'));
                }
                return str;

            }
        }

        public bool IsRoot
        {
            get { return BaseSirenClass == null; }
        }


        public SirenClass(Type type, SirenClassAttribute attribute)
        {
            Type = type;
            Attribute = attribute;
            IncludeTypes = new HashSet<Type>();
        }

        private void AddIncludeType(Type type)
        {
            var attr = type.GetCustomAttribute<SirenClassAttribute>();
            if (attr == null)
            {
                return;
            }

            if (!IncludeTypes.Contains(type))
            {
                IncludeTypes.Add(type);
            }
        }

        public bool Initialzie()
        {
            //get template
            Template = SirenFactory.Create(Attribute.Template) as ISirenTemplate;
            if (Template == null)
            {
                return false;
            }

            if (Type.IsEnum)
            {
                return true;
            }

            //get methods
            SerializeMethodInfo = Type.GetMethod("Serialize", BindingFlags.Public | BindingFlags.Instance);
            DeserializeMethodInfo = Type.GetMethod("Deserialize", BindingFlags.Public | BindingFlags.Instance);
            RegisterMethodInfo = Type.GetMethod("Register", BindingFlags.Public | BindingFlags.Instance|BindingFlags.Static);
            if (RegisterMethodInfo!=null&&!Type.ContainsGenericParameters)
            {
                RegisterMethodInfo.Invoke(null, null);
            }
            

            //get properties
            uint index = 0;
            ushort id = GetBasePropertyCount();
            var properties = Type.GetProperties(BindingFlags.DeclaredOnly | BindingFlags.Public | BindingFlags.Instance);
            foreach (var propertyInfo in properties)
            {
                SirenPropertyAttribute propertyAttribute = propertyInfo.GetCustomAttribute<SirenPropertyAttribute>();
                if (propertyAttribute != null)
                {
                    SirenProperty property = new SirenProperty(this, propertyInfo, propertyAttribute, index++, id++);
                    Properties.Add(property);
                    PropertyIdDict.Add(property.Id, property);
                    PropertyNameDict.Add(property.Name, property);
                }
            }

            if (Properties.Count == 0)
            {
                if (Type.BaseType == typeof (object) || Type.BaseType.IsValueType)
                {
                    return false;
                }
            }


            //get include types
            foreach (var property in Properties)
            {
                var type = property.Type;
                if (type.IsGenericType)
                {
                    if (type.Name.StartsWith("List"))
                    {
                        var valueType = type.GenericTypeArguments[0];
                        AddIncludeType(valueType);

                    }
                    else if (type.Name.StartsWith("Dictionary"))
                    {
                        var keyType = type.GenericTypeArguments[0];
                        var valueType = type.GenericTypeArguments[1];
                        AddIncludeType(keyType);
                        AddIncludeType(valueType);
                    }
                    else
                    {
                        AddIncludeType(type);
                    }
                }
                else
                {
                    AddIncludeType(type);
                }
               
               
            }

            if (Type.BaseType != typeof(object)&&!Type.BaseType.IsValueType)
            {
                //has base type
                if (!IncludeTypes.Contains(Type.BaseType))
                {
                    IncludeTypes.Add(Type.BaseType);
                }

                BaseSirenClass = SirenFactory.FindClass(Type.BaseType);
                if (BaseSirenClass != null)
                {
                    //add base properties
                    foreach (var sirenProperty in BaseSirenClass.PropertyIdDict)
                    {
                        PropertyIdDict.Add(sirenProperty.Key, sirenProperty.Value);
                    }

                    foreach (var sirenProperty in BaseSirenClass.PropertyNameDict)
                    {
                        PropertyNameDict.Add(sirenProperty.Key, sirenProperty.Value);
                    }
                }
            }


            return true;
        }

        public ushort GetBasePropertyCount()
        {
            if (Type.BaseType != typeof(object))
            {
                var baseClass = SirenFactory.FindClass(Type.BaseType);
                if (baseClass != null)
                {
                    return (ushort)(baseClass.GetBasePropertyCount() + (ushort)baseClass.Properties.Count);
                }
            }
            return 0;
        }

        public override string ToString()
        {
            return Name;
        }

        public SirenProperty FindProperty(ushort id)
        {
            SirenProperty outProperty;
            PropertyIdDict.TryGetValue(id, out outProperty);
            return outProperty;
        }

        public SirenProperty FindProperty(String name)
        {
            SirenProperty outProperty;
            PropertyNameDict.TryGetValue(name, out outProperty);
            return outProperty;
        }
    }


}
