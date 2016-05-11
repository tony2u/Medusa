// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using Siren;
using Siren.Attribute;
using Siren.Protocol;

namespace Medusa
{
    [SirenClass(typeof(MedusaTemplate), @"Geometry", SirenGenerateMode.Suppress, NewHeader = "Point2")]
    public class Point2<T>
    {
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T X { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T Y { get; set; }

        public static void Register()
        {
            SirenFactory.RegisterTypeName<Point2<float>>("Point2F");
            SirenFactory.RegisterTypeName<Point2<uint>>("Point2U");
        }

        public void Serialize(BaseProtocolWriter writer)
        {
            writer.OnStructBegin();
            writer.OnProperty("X", 0, X, false);
            writer.OnProperty("Y", 1, Y, false);
            writer.OnStructEnd();
        }

        public void Deserialize(BaseProtocolReader reader)
        {
            reader.OnStructBegin();
            X = reader.OnProperty<T>("X", 0, false);
            Y = reader.OnProperty<T>("Y", 1, false);
            reader.OnStructEnd();
        }
    }

    [SirenClass(typeof(MedusaTemplate), @"Geometry", SirenGenerateMode.Suppress, NewHeader = "Size2")]
    public class Size2<T>
    {
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T Width { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T Height { get; set; }

        public static void Register()
        {
            SirenFactory.RegisterTypeName<Size2<float>>("Size2F");
            SirenFactory.RegisterTypeName<Size2<uint>>("Size2U");
        }

        public void Serialize(BaseProtocolWriter writer)
        {
            writer.OnStructBegin();
            writer.OnProperty("Width", 0, Width, false);
            writer.OnProperty("Height", 1, Height, false);
            writer.OnStructEnd();
        }

        public void Deserialize(BaseProtocolReader reader)
        {
            reader.OnStructBegin();
            Width = reader.OnProperty<T>("Width", 0, false);
            Height = reader.OnProperty<T>("Height", 1, false);
            reader.OnStructEnd();
        }
    }

    [SirenClass(typeof(MedusaTemplate), @"Geometry", SirenGenerateMode.Suppress, NewHeader = "Scale2")]
    public class Scale2<T>
    {
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T X { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T Y { get; set; }

        public static void Register()
        {
            SirenFactory.RegisterTypeName<Scale2<float>>("Scale2F");
            SirenFactory.RegisterTypeName<Scale2<uint>>("Scale2U");
        }

        public void Serialize(BaseProtocolWriter writer)
        {
            writer.OnStructBegin();
            writer.OnProperty("X", 0, X, false);
            writer.OnProperty("Y", 1, Y, false);
            writer.OnStructEnd();
        }

        public void Deserialize(BaseProtocolReader reader)
        {
            reader.OnStructBegin();
            X = reader.OnProperty<T>("X", 0, false);
            Y = reader.OnProperty<T>("Y", 1, false);
            reader.OnStructEnd();
        }
    }

    [SirenClass(typeof(MedusaTemplate), @"Geometry", SirenGenerateMode.Suppress, NewHeader = "Range")]
    public class Range<T>
    {
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T Min { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T Max { get; set; }

        public static void Register()
        {
            SirenFactory.RegisterTypeName<Range<float>>("RangeF");
            SirenFactory.RegisterTypeName<Range<uint>>("RangeU");
        }


        public void Serialize(BaseProtocolWriter writer)
        {
            writer.OnStructBegin();
            writer.OnProperty("Min", 0, Min, false);
            writer.OnProperty("Max", 1, Max, false);
            writer.OnStructEnd();
        }

        public void Deserialize(BaseProtocolReader reader)
        {
            reader.OnStructBegin();
            Min = reader.OnProperty<T>("Min", 0, false);
            Max = reader.OnProperty<T>("Max", 1, false);
            reader.OnStructEnd();
        }
    }

    [SirenClass(typeof(MedusaTemplate), @"Geometry", SirenGenerateMode.Suppress, NewHeader = "Rect2")]
    public class Rect2<T>
    {
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public Point2<T> Origin { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public Size2<T> Size { get; set; }

        public static void Register()
        {
            SirenFactory.RegisterTypeName<Rect2<float>>("Rect2F");
            SirenFactory.RegisterTypeName<Rect2<uint>>("Rect2U");
        }


        public void Serialize(BaseProtocolWriter writer)
        {
            writer.OnStructBegin();
            writer.OnProperty("Origin", 0, Origin, false);
            writer.OnProperty("Size", 1, Size, false);
            writer.OnStructEnd();
        }

        public void Deserialize(BaseProtocolReader reader)
        {
            reader.OnStructBegin();
            Origin = reader.OnProperty<Point2<T>>("Origin", 0, false);
            Size = reader.OnProperty<Size2<T>>("Size", 1, false);
            reader.OnStructEnd();
        }
    }

    [SirenClass(typeof(MedusaTemplate), @"Geometry", SirenGenerateMode.Suppress, NewHeader = "Padding4")]
    public class Padding4<T>
    {
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T Left { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T Right { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T Up { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public T Down { get; set; }

        public static void Register()
        {
            SirenFactory.RegisterTypeName<Padding4<float>>("Padding4F");
            SirenFactory.RegisterTypeName<Padding4<uint>>("Padding4U");
        }


        public void Serialize(BaseProtocolWriter writer)
        {
            writer.OnStructBegin();
            writer.OnProperty("Left", 0, Left, false);
            writer.OnProperty("Right", 1, Right, false);
            writer.OnProperty("Up", 2, Up, false);
            writer.OnProperty("Down", 3, Down, false);

            writer.OnStructEnd();
        }

        public void Deserialize(BaseProtocolReader reader)
        {
            reader.OnStructBegin();
            Left = reader.OnProperty<T>("Left", 0, false);
            Right = reader.OnProperty<T>("Right", 1, false);
            Up = reader.OnProperty<T>("Up", 2, false);
            Down = reader.OnProperty<T>("Down", 3, false);

            reader.OnStructEnd();
        }
    }


    [SirenClass(typeof(MedusaTemplate), @"Geometry", SirenGenerateMode.Suppress, NewHeader = "Color4")]
    public class Color4F
    {
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public float R { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public float G { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public float B { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public float A { get; set; }


        public void Serialize(BaseProtocolWriter writer)
        {
            writer.OnStructBegin();
            writer.OnProperty("R", 0, R, false);
            writer.OnProperty("G", 1, G, false);
            writer.OnProperty("B", 2, B, false);
            writer.OnProperty("A", 3, A, false);

            writer.OnStructEnd();
        }

        public void Deserialize(BaseProtocolReader reader)
        {
            reader.OnStructBegin();
            R = reader.OnProperty<float>("R", 0, false);
            G = reader.OnProperty<float>("G", 1, false);
            B = reader.OnProperty<float>("B", 2, false);
            A = reader.OnProperty<float>("A", 3, false);

            reader.OnStructEnd();
        }
    }


    [SirenClass(typeof(MedusaTemplate), @"Geometry", SirenGenerateMode.Suppress, NewHeader = "Color4")]
    public class Color4B
    {
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public byte R { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public byte G { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public byte B { get; set; }
        [SirenProperty(SirenPropertyModifier.Required, 0)]
        public byte A { get; set; }


        public void Serialize(BaseProtocolWriter writer)
        {
            writer.OnStructBegin();
            writer.OnProperty("R", 0, R, false);
            writer.OnProperty("G", 1, G, false);
            writer.OnProperty("B", 2, B, false);
            writer.OnProperty("A", 3, A, false);

            writer.OnStructEnd();
        }

        public void Deserialize(BaseProtocolReader reader)
        {
            reader.OnStructBegin();
            R = reader.OnProperty<byte>("R", 0, false);
            G = reader.OnProperty<byte>("G", 1, false);
            B = reader.OnProperty<byte>("B", 2, false);
            A = reader.OnProperty<byte>("A", 3, false);

            reader.OnStructEnd();
        }
    }
}
