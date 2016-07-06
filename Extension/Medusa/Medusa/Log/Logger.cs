// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System;
using static System.String;

namespace Medusa.Log
{
    public static class Logger
    {
        public static event Action<string> OnInfo;
        public static event Action<string> OnError;

        public static void Info(string format, params object[] objects)
        {
            string str = Format(format, objects);
            OnInfo?.Invoke(str);

        }

        public static void Error(string format, params object[] objects)
        {
            string str = Format(format, objects);
            OnError?.Invoke(str);
        }

        public static void All(string format, params object[] objects)
        {
            string str = Format(format, objects);

            OnInfo?.Invoke(str);
            OnError?.Invoke(str);
        }

        public static void InfoLine(string format, params object[] objects)
        {
            string str = Format(format, objects) + "\n";
            OnInfo?.Invoke(str);
        }

        public static void ErrorLine(string format, params object[] objects)
        {
            string str = Format(format, objects) + "\n";
            OnError?.Invoke(str);
        }

        public static void AllLine(string format, params object[] objects)
        {
            string str = Format(format, objects) + "\n";
            OnInfo?.Invoke(str);
            OnError?.Invoke(str);
        }
    }
}