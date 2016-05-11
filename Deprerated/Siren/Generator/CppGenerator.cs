// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Text;

namespace Siren.Generator
{
    public class CppGenerator : BaseGenerator
    {
        private const string mHeaderIncludeMask = "<SIREN_HEADER_INCLUDE>";
        private const string mHeaderMask = "<SIREN_HEADER>";
        private const string mBodyIncludeMask = "<SIREN_BODY_INCLUDE>";
        private const string mBodyMask = "<SIREN_BODY>";


        private const string mHeaderIncludeBegin = "//SIREN_HEADER_INCLUDE_BEGIN";
        private const string mHeaderIncludeEnd = "//SIREN_HEADER_INCLUDE_END";

        private const string mHeaderCopyBegin = "//SIREN_HEADER_COPY_BEGIN";
        private const string mHeaderCopyEnd = "//SIREN_HEADER_COPY_END";

        private const string mHeaderCompareBegin = "//SIREN_HEADER_COMPARE_BEGIN";
        private const string mHeaderCompareEnd = "//SIREN_HEADER_COMPARE_END";

        private const string mHeaderMethodBegin = "//SIREN_HEADER_METHOD_BEGIN";
        private const string mHeaderMethodEnd = "//SIREN_HEADER_METHOD_END";

        private const string mHeaderFieldBegin = "//SIREN_HEADER_FIELD_BEGIN";
        private const string mHeaderFieldEnd = "//SIREN_HEADER_FIELD_END";


        private const string mHeaderSchemaBegin = "//SIREN_HEADER_SCHEMA_BEGIN";
        private const string mHeaderSchemaEnd = "//SIREN_HEADER_SCHEMA_END";


        private const string mBodyIncludeBegin = "//SIREN_BODY_INCLUDE_BEGIN";
        private const string mBodyIncludeEnd = "//SIREN_BODY_INCLUDE_END";

        private const string mBodyConstructBegin = "//SIREN_BODY_CONSTRUCT_BEGIN";
        private const string mBodyConstructEnd = "//SIREN_BODY_CONSTRUCT_END";
        private const string mBodyDestructBegin = "//SIREN_BODY_DESTRUCT_BEGIN";
        private const string mBodyDestructEnd = "//SIREN_BODY_DESTRUCT_END";

        private const string mBodyMetadataBegin = "//SIREN_BODY_METADATA_BEGIN";
        private const string mBodyMetadataEnd = "//SIREN_BODY_METADATA_END";

        public override void GenerateClass(SirenClass sirenClass)
        {
            var hName = sirenClass.Type.Name + ".h";
            var cppName = sirenClass.Type.Name + ".cpp";

            var hPath = Path.Combine(WorkingDirectory.FullName, sirenClass.Template.RootDirectory, sirenClass.Attribute.Directory, hName);
            var cppPath = Path.Combine(WorkingDirectory.FullName, sirenClass.Template.RootDirectory, sirenClass.Attribute.Directory, cppName);


            //get properties
            if (sirenClass.Type.IsEnum)
            {
                StringBuilder header = new StringBuilder(sirenClass.Template.HeaderTemplate);

                var headerInclude = GenerateHeaderInclude(sirenClass);
                var headerStr = GenerateEnumHeader(sirenClass);
                header.Replace(mHeaderIncludeMask, headerInclude);
                header.Replace(mHeaderMask, headerStr);

                UpdateFile(hPath, header.ToString());
            }
            else if (sirenClass.Attribute.Mode.HasFlag(SirenGenerateMode.Generate) || !File.Exists(hPath) || !File.Exists(cppPath))
            {
                StringBuilder header = new StringBuilder(sirenClass.Template.HeaderTemplate);
                StringBuilder body = new StringBuilder(sirenClass.Template.BodyTemplate);

                var headerInclude = GenerateAllHeaderInclude(sirenClass);
                var headerStr = GenerateAllHeader(sirenClass);
                header.Replace(mHeaderIncludeMask, headerInclude);
                header.Replace(mHeaderMask, headerStr);

                var bodyInclude = GenerateAllBodyInclude(sirenClass);
                var bodyStr = GenerateAllBody(sirenClass);
                body.Replace(mBodyIncludeMask, bodyInclude);
                body.Replace(mBodyMask, bodyStr);


                UpdateFile(hPath, header.ToString());
                UpdateFile(cppPath, body.ToString());
            }
            else
            {
                string header = File.ReadAllText(hPath);
                string body = File.ReadAllText(cppPath);



                var headerInclude = GenerateHeaderInclude(sirenClass);
                headerInclude = "\r\n" + headerInclude;
                header = Replace(header, mHeaderIncludeBegin, mHeaderIncludeEnd, headerInclude);

                if (!sirenClass.Attribute.Mode.HasFlag(SirenGenerateMode.SuppressCompare))
                {
                    var hederCompare = GenerateHeaderCompare(sirenClass);
                    hederCompare = "\r\n" + hederCompare;
                    header = Replace(header, mHeaderCompareBegin, mHeaderCompareEnd, hederCompare);
                }

                if (!sirenClass.Attribute.Mode.HasFlag(SirenGenerateMode.SuppressCopy))
                {
                    var hederCopy = GenerateHeaderCopy(sirenClass);
                    hederCopy = "\r\n" + hederCopy;
                    header = Replace(header, mHeaderCopyBegin, mHeaderCopyEnd, hederCopy);
                }


                var hederMethod = GenerateHeaderMethod(sirenClass);
                hederMethod = "\r\n" + hederMethod;
                header = Replace(header, mHeaderMethodBegin, mHeaderMethodEnd, hederMethod);

                var hederField = GenerateHeaderField(sirenClass);
                hederField = "\r\n" + hederField;
                header = Replace(header, mHeaderFieldBegin, mHeaderFieldEnd, hederField);

                var hederSchema = GenerateHeaderSchema(sirenClass);
                hederSchema = "\r\n" + hederSchema;
                header = Replace(header, mHeaderSchemaBegin, mHeaderSchemaEnd, hederSchema);


                var bodyInclude = GenerateBodyInclude(sirenClass);
                bodyInclude = "\r\n" + bodyInclude;
                body = Replace(body, mBodyIncludeBegin, mBodyIncludeEnd, bodyInclude);

                var bodyConstruct = GenerateBodyConstruct(sirenClass);
                bodyConstruct = "\r\n" + bodyConstruct;
                body = Replace(body, mBodyConstructBegin, mBodyConstructEnd, bodyConstruct);

                var bodyDestruct = GenerateBodyDestruct(sirenClass);
                bodyDestruct = "\r\n" + bodyDestruct;
                body = Replace(body, mBodyDestructBegin, mBodyDestructEnd, bodyDestruct);

                var bodySchema = GenerateBodyMetadata(sirenClass);
                bodySchema = "\r\n" + bodySchema;
                body = Replace(body, mBodyMetadataBegin, mBodyMetadataEnd, bodySchema);


                UpdateFile(hPath, header);
                UpdateFile(cppPath, body);
            }


        }

        public string GenerateAllHeaderInclude(SirenClass sirenClass)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine(mHeaderIncludeBegin);
            sb.Append(GenerateHeaderInclude(sirenClass));
            sb.AppendLine(mHeaderIncludeEnd);

            return sb.ToString();
        }


        public string GenerateHeaderInclude(SirenClass sirenClass)
        {
            StringBuilder sb = new StringBuilder();
            //sb.AppendLine();
            foreach (var includeType in sirenClass.IncludeTypes)
            {
                var includeSirenClass = SirenFactory.FindClass(includeType);
                if (includeSirenClass != null)
                {
                    if (!string.IsNullOrEmpty(includeSirenClass.Attribute.NewHeader))
                    {
                        sb.AppendFormat("#include \"{0}/{1}.h\"\r\n", includeSirenClass.Attribute.Directory, includeSirenClass.Attribute.NewHeader);
                    }
                    else
                    {
                        sb.AppendFormat("#include \"{0}/{1}.h\"\r\n", includeSirenClass.Attribute.Directory, SirenFactory.GetTypeName(includeType));
                    }
                }
                else
                {
                    sb.AppendFormat("#include \"{0}.h\"\r\n", SirenFactory.GetTypeName(includeType));
                }
            }

            if (sirenClass.Attribute.Mode.HasFlag(SirenGenerateMode.SirenConfig))
            {
                sb.AppendFormat("#include \"Core/Siren/ISirenConfig.h\"\r\n");
            }
            return sb.ToString();
        }

        public string GenerateAllHeader(SirenClass sirenClass)
        {
            var typeName = sirenClass.Name;
            StringBuilder sb = new StringBuilder();
            if (!sirenClass.Attribute.IsEmbeded)
            {
                if (sirenClass.IsRoot)
                {
                    if (sirenClass.Attribute.Mode.HasFlag(SirenGenerateMode.SirenConfig))
                    {
                        sb.AppendFormat("class {0} : public ISirenConfig<{1}>\r\n", typeName, typeName);

                    }
                    else
                    {
                        sb.AppendFormat("class {0}\r\n", typeName);
                    }
                }
                else
                {
                    if (sirenClass.Attribute.Mode.HasFlag(SirenGenerateMode.SirenConfig))
                    {
                        sb.AppendFormat("class {0} : public {1},public ISirenConfig<{2}>\r\n", typeName, sirenClass.BaseSirenClass.Name, typeName);
                    }
                    else
                    {
                        sb.AppendFormat("class {0} : public {1}\r\n", typeName, sirenClass.BaseSirenClass.Name);

                    }
                }
                sb.AppendLine("{");
            }

            sb.Append(GenerateHeaderConstruct(sirenClass));

            if (!sirenClass.Attribute.Mode.HasFlag(SirenGenerateMode.SuppressCompare))
            {
                sb.AppendLine(mHeaderCopyBegin);
                sb.Append(GenerateHeaderCopy(sirenClass));
                sb.AppendLine(mHeaderCopyEnd);
            }

            if (!sirenClass.Attribute.Mode.HasFlag(SirenGenerateMode.SuppressCompare))
            {
                sb.AppendLine(mHeaderCompareBegin);
                sb.Append(GenerateHeaderCompare(sirenClass));
                sb.AppendLine(mHeaderCompareEnd);
            }

            //add method
            sb.AppendLine(mHeaderMethodBegin);
            sb.Append(GenerateHeaderMethod(sirenClass));
            sb.AppendLine(mHeaderMethodEnd);

            //add fields
            sb.AppendLine(mHeaderFieldBegin);
            sb.Append(GenerateHeaderField(sirenClass));
            sb.AppendLine(mHeaderFieldEnd);

            sb.AppendLine("};");
            sb.AppendLine();

            sb.AppendLine(mHeaderSchemaBegin);
            sb.AppendLine(GenerateHeaderSchema(sirenClass));
            sb.AppendLine(mHeaderSchemaEnd);
            return sb.ToString();


        }

        public string GenerateHeaderConstruct(SirenClass sirenClass)
        {
            var typeName = sirenClass.Name;
            StringBuilder sb = new StringBuilder();
            //sb.AppendLine();

            sb.AppendLine("public:");
            sb.AppendLine("\tstruct Schema;");
            sb.AppendFormat("\t{0}();\r\n", typeName);
            sb.AppendFormat("\t~{0}();\r\n", typeName);

            return sb.ToString();

        }

        public string GenerateHeaderCompare(SirenClass sirenClass)
        {
            var typeName = sirenClass.Name;
            StringBuilder sb = new StringBuilder();
            //sb.AppendLine();

            sb.AppendLine("public:");
            //sb.AppendFormat("\tbool operator<(const {0}&)const { return true; }\r\n", typeName);
            //sb.AppendFormat("\tbool operator==(const {0}&)const { return true; }\r\n", typeName);



            sb.AppendFormat("\tSIREN_COMMON({0});\r\n", typeName);

            return sb.ToString();

        }

        public string GenerateHeaderCopy(SirenClass sirenClass)
        {
            var typeName = sirenClass.Name;
            StringBuilder sb = new StringBuilder();
            //sb.AppendLine();

            sb.AppendLine("public:");
            //copy construct
            sb.AppendFormat("\t{0}(const {1}& other)\r\n", typeName, typeName);
            sb.AppendFormat("\t{{\r\n");
            foreach (var sirenProperty in sirenClass.Properties)
            {
                var methodType = sirenProperty.MethodType;
                switch (methodType)
                {
                    case SirenPropertyMethodType.Pointer:
                        sb.AppendFormat("\t\tSAFE_CONSTRUCT_PTR({0},m{1},other.m{2});\r\n", SirenFactory.GetTypeName(sirenProperty.Type), sirenProperty.Name, sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.Value:
                    case SirenPropertyMethodType.List:
                    case SirenPropertyMethodType.Dictionary:
                        sb.AppendFormat("\t\tm{0} = other.m{1};\r\n", sirenProperty.Name, sirenProperty.Name);
                        break;
                }

            }
            sb.AppendFormat("\t}}\r\n");

            //assign 
            sb.AppendFormat("\t{0}& operator=(const {1}& other)\r\n", typeName, typeName);
            sb.AppendFormat("\t{{\r\n");
            foreach (var sirenProperty in sirenClass.Properties)
            {
                var methodType = sirenProperty.MethodType;
                switch (methodType)
                {
                    case SirenPropertyMethodType.Pointer:

                        sb.AppendFormat("\t\tSAFE_COPY_PTR({0},m{1},other.m{2});\r\n", SirenFactory.GetTypeName(sirenProperty.Type), sirenProperty.Name, sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.Value:
                    case SirenPropertyMethodType.List:
                    case SirenPropertyMethodType.Dictionary:
                        sb.AppendFormat("\t\tm{0} = other.m{1};\r\n", sirenProperty.Name, sirenProperty.Name);
                        break;
                }
            }
            sb.AppendFormat("\t\treturn *this;\r\n");

            sb.AppendFormat("\t}}\r\n");


            return sb.ToString();

        }


        public string GenerateHeaderMethod(SirenClass sirenClass)
        {
            StringBuilder sb = new StringBuilder();
            //sb.AppendLine();

            //add methods
            sb.AppendLine("public:");
            foreach (var sirenProperty in sirenClass.Properties)
            {
                if (sirenProperty.Attribute.SuppressMethod)
                {
                    continue;
                }

                var methodType = sirenProperty.MethodType;
                switch (methodType)
                {
                    case SirenPropertyMethodType.Value:
                        sb.AppendFormat("\tSIREN_METHOD({0}, {1});\r\n", SirenFactory.GetTypeName(sirenProperty.Type), sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.Pointer:
                        sb.AppendFormat("\tSIREN_METHOD_PTR({0}, {1});\r\n", SirenFactory.GetTypeName(sirenProperty.Type), sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.List:
                        var itemType = sirenProperty.Type.GenericTypeArguments[0];
                        sb.AppendFormat("\tSIREN_METHOD_LIST({0}, {1});\r\n", SirenFactory.GetTypeName(itemType, sirenProperty.Attribute.ForceValueToPtr), sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.Dictionary:
                        var keyType = sirenProperty.Type.GenericTypeArguments[0];
                        var valueType = sirenProperty.Type.GenericTypeArguments[1];
                        if (sirenProperty.Attribute.AddDictionaryMethods)
                        {
                            sb.AppendFormat("\tSIREN_METHOD_DICTIONARY_EX({0}, {1}, {2});\r\n", SirenFactory.GetTypeName(keyType, sirenProperty.Attribute.ForceKeyToPtr), SirenFactory.GetTypeName(valueType, sirenProperty.Attribute.ForceValueToPtr), sirenProperty.Name);
                        }
                        else
                        {
                            sb.AppendFormat("\tSIREN_METHOD_DICTIONARY({0}, {1}, {2});\r\n", SirenFactory.GetTypeName(keyType, sirenProperty.Attribute.ForceKeyToPtr), SirenFactory.GetTypeName(valueType, sirenProperty.Attribute.ForceValueToPtr), sirenProperty.Name);
                        }


                        break;
                }

            }

            return sb.ToString();

        }
        public string GenerateHeaderField(SirenClass sirenClass)
        {
            StringBuilder sb = new StringBuilder();
            //sb.AppendLine();

            //add fields
            sb.AppendLine("protected:");
            foreach (var sirenProperty in sirenClass.Properties)
            {
                var methodType = sirenProperty.MethodType;
                switch (methodType)
                {
                    case SirenPropertyMethodType.Value:
                        sb.AppendFormat("\t{0} m{1};\r\n", SirenFactory.GetTypeName(sirenProperty.Type), sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.Pointer:
                        sb.AppendFormat("\t{0}* m{1};\r\n", SirenFactory.GetTypeName(sirenProperty.Type), sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.List:
                        var itemType = sirenProperty.Type.GenericTypeArguments[0];
                        sb.AppendFormat("\tList<{0}> m{1};\r\n", SirenFactory.GetTypeName(itemType, sirenProperty.Attribute.ForceValueToPtr), sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.Dictionary:
                        var keyType = sirenProperty.Type.GenericTypeArguments[0];
                        var valueType = sirenProperty.Type.GenericTypeArguments[1];
                        sb.AppendFormat("\tDictionary<{0}, {1}> m{2};\r\n", SirenFactory.GetTypeName(keyType, sirenProperty.Attribute.ForceKeyToPtr), SirenFactory.GetTypeName(valueType, sirenProperty.Attribute.ForceValueToPtr), sirenProperty.Name);
                        break;
                }

            }

            return sb.ToString();

        }

        public string GenerateHeaderSchema(SirenClass sirenClass)
        {
            var typeName = sirenClass.Name;
            StringBuilder sb = new StringBuilder();
            //sb.AppendLine();

            //add schema
            sb.AppendFormat("struct {0}::Schema\r\n", typeName);
            sb.AppendLine("{");

            foreach (var sirenProperty in sirenClass.Properties)
            {
                var methodType = sirenProperty.MethodType;
                switch (methodType)
                {
                    case SirenPropertyMethodType.Value:
                        sb.AppendFormat("\tSIREN_PROPERTY({0}, {1}, {2}, {3}, {4}, m{5});\r\n", sirenProperty.Index, sirenProperty.Id, sirenProperty.Attribute.Modifier, typeName, SirenFactory.GetTypeName(sirenProperty.Type), sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.Pointer:
                        sb.AppendFormat("\tSIREN_PROPERTY({0}, {1}, {2}, {3}, {4}*, m{5});\r\n", sirenProperty.Index, sirenProperty.Id, sirenProperty.Attribute.Modifier, typeName, SirenFactory.GetTypeName(sirenProperty.Type), sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.List:
                        var itemType = sirenProperty.Type.GenericTypeArguments[0];
                        sb.AppendFormat("\tSIREN_PROPERTY_LIST({0}, {1}, {2}, {3}, {4}, m{5});\r\n", sirenProperty.Index, sirenProperty.Id, sirenProperty.Attribute.Modifier, typeName, SirenFactory.GetTypeName(itemType, sirenProperty.Attribute.ForceValueToPtr), sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.Dictionary:
                        var keyType = sirenProperty.Type.GenericTypeArguments[0];
                        var valueType = sirenProperty.Type.GenericTypeArguments[1];
                        sb.AppendFormat("\tSIREN_PROPERTY_DICTIONARY({0}, {1}, {2}, {3}, {4}, {5}, m{6});\r\n", sirenProperty.Index, sirenProperty.Id, sirenProperty.Attribute.Modifier, typeName, SirenFactory.GetTypeName(keyType, sirenProperty.Attribute.ForceKeyToPtr), SirenFactory.GetTypeName(valueType, sirenProperty.Attribute.ForceValueToPtr), sirenProperty.Name);
                        break;
                }
            }

            //add properties
            if (sirenClass.IsRoot)
            {
                sb.AppendFormat("\tSIREN_PROPERTIES_{0}(void,{1});\r\n", sirenClass.Properties.Count, typeName);
            }
            else
            {
                sb.AppendFormat("\tSIREN_PROPERTIES_{0}({1},{2});\r\n", sirenClass.Properties.Count, sirenClass.BaseSirenClass.Name, typeName);
            }

            sb.Append("};");



            return sb.ToString();


        }

        public string GenerateAllBodyInclude(SirenClass sirenClass)
        {
            StringBuilder sb = new StringBuilder();
            //sb.AppendLine();
            sb.AppendLine(mBodyIncludeBegin);
            sb.Append(GenerateBodyInclude(sirenClass));
            sb.AppendLine(mBodyIncludeEnd);

            return sb.ToString();

        }

        public string GenerateBodyInclude(SirenClass sirenClass)
        {
            StringBuilder sb = new StringBuilder();
            //sb.AppendLine();

            sb.AppendFormat("#include \"{0}.h\"\r\n", sirenClass.Type.Name);

            return sb.ToString();

        }


        public string GenerateAllBody(SirenClass sirenClass)
        {
            var typeName = sirenClass.Name;
            StringBuilder sb = new StringBuilder();

            sb.AppendFormat("{0}::{1}()\r\n", typeName, typeName);
            sb.AppendLine("{");
            sb.AppendLine(mBodyConstructBegin);
            sb.Append(GenerateBodyConstruct(sirenClass));
            sb.AppendLine(mBodyConstructEnd);

            sb.AppendLine("}");
            sb.AppendLine();

            sb.AppendFormat("{0}::~{1}()\r\n", typeName, typeName);
            sb.AppendLine("{");
            sb.AppendLine(mBodyDestructBegin);
            sb.Append(GenerateBodyDestruct(sirenClass));
            sb.AppendLine(mBodyDestructEnd);

            sb.AppendLine("}");
            sb.AppendLine();

            sb.AppendLine(mBodyMetadataBegin);
            sb.Append(GenerateBodyMetadata(sirenClass));
            sb.AppendLine(mBodyMetadataEnd);


            return sb.ToString();
        }

        public string GenerateBodyConstruct(SirenClass sirenClass)
        {
            var typeName = sirenClass.Name;
            StringBuilder sb = new StringBuilder();
            //sb.AppendLine();

            //add construct
            //add default assignment
            foreach (var sirenProperty in sirenClass.Properties)
            {
                var fieldType = sirenProperty.FieldType;
                switch (fieldType)
                {
                    case SirenPropertyFieldType.Value:
                        sb.AppendFormat("\tm{0} = {1};\r\n", sirenProperty.Name, sirenProperty.DefaultValueString);
                        break;
                    case SirenPropertyFieldType.Pointer:
                        sb.AppendFormat("\tm{0} = NULL;\r\n", sirenProperty.Name);
                        break;
                }
            }

            return sb.ToString();
        }

        public string GenerateBodyDestruct(SirenClass sirenClass)
        {
            var typeName = sirenClass.Name;
            StringBuilder sb = new StringBuilder();
            // sb.AppendLine();

            //add destruct

            foreach (var sirenProperty in sirenClass.Properties)
            {
                var methodType = sirenProperty.MethodType;
                switch (methodType)
                {
                    case SirenPropertyMethodType.Pointer:
                        sb.AppendFormat("\tSAFE_DELETE(m{0});\r\n", sirenProperty.Name);
                        break;
                    case SirenPropertyMethodType.List:
                        if (sirenProperty.Attribute.ForceValueToPtr)
                        {
                            sb.AppendFormat("\tSAFE_DELETE_COLLECTION(m{0});\r\n", sirenProperty.Name);
                        }
                        break;
                    case SirenPropertyMethodType.Dictionary:
                        if (sirenProperty.Attribute.ForceKeyToPtr)
                        {
                            if (sirenProperty.Attribute.ForceValueToPtr)
                            {
                                sb.AppendFormat("\tSAFE_DELETE_DICTIONARY_BOTH(m{0});\r\n", sirenProperty.Name);
                            }
                            else
                            {
                                sb.AppendFormat("\tSAFE_DELETE_DICTIONARY_KEY(m{0});\r\n", sirenProperty.Name);
                            }
                        }
                        else
                        {
                            if (sirenProperty.Attribute.ForceValueToPtr)
                            {
                                sb.AppendFormat("\tSAFE_DELETE_DICTIONARY_VALUE(m{0});\r\n", sirenProperty.Name);
                            }
                            else
                            {
                            }
                        }

                        break;
                }
            }

            return sb.ToString();
        }


        public string GenerateBodyMetadata(SirenClass sirenClass)
        {
            var typeName = sirenClass.Name;
            StringBuilder sb = new StringBuilder();
            // sb.AppendLine();

            //add class metadata
            sb.AppendFormat("SIREN_METADATA({0}, {1});\r\n", typeName, typeName.Length);

            //add property metadata
            int index = 0;
            foreach (var sirenProperty in sirenClass.Properties)
            {
                var fieldType = sirenProperty.FieldType;
                switch (fieldType)
                {
                    case SirenPropertyFieldType.Value:
                        {
                            bool hasDefault = sirenProperty.Attribute.DefaultValue != null;
                            string str2 = hasDefault.ToString().ToLower();
                            sb.AppendFormat("SIREN_PROPERTY_METADATA({0}, {1}, {2}, {3}, {4}, {5});\r\n", index, typeName, sirenProperty.Name, sirenProperty.Name.Length, sirenProperty.DefaultValueString, str2);
                        }

                        break;
                    case SirenPropertyFieldType.Pointer:
                    case SirenPropertyFieldType.Struct:
                    case SirenPropertyFieldType.String:
                    case SirenPropertyFieldType.Blob:
                    case SirenPropertyFieldType.List:
                    case SirenPropertyFieldType.Dictionary:
                        sb.AppendFormat("SIREN_PROPERTY_METADATA_STRUCT({0}, {1}, {2}, {3});\r\n", index, typeName, sirenProperty.Name, sirenProperty.Name.Length);
                        break;
                }
                ++index;
            }

            return sb.ToString();


        }

        public string GenerateEnumHeader(SirenClass sirenClass)
        {
            var typeName = sirenClass.Name;
            StringBuilder sb = new StringBuilder();
            var names = Enum.GetNames(sirenClass.Type);
            var values = Enum.GetValues(sirenClass.Type);
            int count = names.Length;

            switch (sirenClass.Attribute.Mode)
            {
                case SirenGenerateMode.CustomEnum:
                    sb.AppendFormat("STRONG_ENUM_CUSTOM_{0}({1}", count, typeName);
                    for (int i = 0; i < count; i++)
                    {
                        var name = names[i];
                        var val = values.GetValue(i);
                        int v = Convert.ToInt32(val);
                        sb.AppendFormat(",{0},{1}", name, v);
                    }
                    sb.AppendLine(");");


                    break;
                case SirenGenerateMode.CustomFlag:
                    sb.AppendFormat("STRONG_FLAGS_CUSTOM_{0}({1}", count, typeName);
                    for (int i = 0; i < count; i++)
                    {
                        var name = names[i];
                        var val = values.GetValue(i);
                        int v = Convert.ToInt32(val);
                        sb.AppendFormat(",{0},{1}", name, v);
                    }
                    sb.AppendLine(");");
                    break;
                default:
                    {
                        if (string.IsNullOrEmpty(sirenClass.Attribute.EnumUnderType))
                        {
                            sb.AppendFormat("enum class {0}\r\n", typeName);
                        }
                        else
                        {
                            sb.AppendFormat("enum class {0}:{1}\r\n", typeName, sirenClass.Attribute.EnumUnderType);
                        }

                        sb.AppendLine("{");

                        for (int i = 0; i < count; i++)
                        {
                            var name = names[i];
                            var val = values.GetValue(i);
                            int v = Convert.ToInt32(val);
                            sb.AppendFormat("\t{0} = {1},\r\n", name, v);
                        }

                        sb.AppendLine("};");

                        break;
                    }
            }


            return sb.ToString();

        }

    }
}
