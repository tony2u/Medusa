// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;

namespace GameKit.Log
{
    public static class Logger
    {
        public static event Action<string> InfoEvent;

        private static void OnInfoEvent(string obj)
        {
            var handler = InfoEvent;
            if (handler != null) handler(obj);
        }

        public static event Action<string> ErrorEvent;

        private static void OnErrorEvent(string obj)
        {
            var handler = ErrorEvent;
            if (handler != null) handler(obj);
        }

        public static void LogInfo(string format, params object[] objects)
        {
            string str = String.Format(format, objects);
            OnInfoEvent(str);
        }

        public static void LogError(string format, params object[] objects)
        {
            string str = String.Format(format, objects);
            OnErrorEvent(str);
        }

        public static void LogAll(string format, params object[] objects)
        {
            string str = String.Format(format, objects);

            OnInfoEvent(str);
            OnErrorEvent(str);
        }

        public static void LogInfoLine(string format, params object[] objects)
        {
            string str = String.Format(format, objects) + "\n";
            OnInfoEvent(str);
        }

        public static void LogErrorLine(string format, params object[] objects)
        {
            string str = String.Format(format, objects) + "\n";
            OnErrorEvent(str);
        }

        public static void LogAllLine(string format, params object[] objects)
        {
            string str = String.Format(format, objects) + "\n";
            OnInfoEvent(str);
            OnErrorEvent(str);
        }
    }
}