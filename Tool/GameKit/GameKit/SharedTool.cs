// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

namespace GameKit
{
    public enum ERROR_ID
    {
        ERROR_SUCCESS = 0, // Success
        ERROR_BUSY = 170,
        ERROR_MORE_DATA = 234,
        ERROR_NO_BROWSER_SERVERS_FOUND = 6118,
        ERROR_INVALID_LEVEL = 124,
        ERROR_ACCESS_DENIED = 5,
        ERROR_INVALID_PASSWORD = 86,
        ERROR_INVALID_PARAMETER = 87,
        ERROR_BAD_DEV_TYPE = 66,
        ERROR_NOT_ENOUGH_MEMORY = 8,
        ERROR_NETWORK_BUSY = 54,
        ERROR_BAD_NETPATH = 53,
        ERROR_NO_NETWORK = 1222,
        ERROR_INVALID_HANDLE_STATE = 1609,
        ERROR_EXTENDED_ERROR = 1208,
        ERROR_DEVICE_ALREADY_REMEMBERED = 1202,
        ERROR_NO_NET_OR_BAD_PATH = 1203
    }

    public enum RESOURCE_SCOPE
    {
        RESOURCE_CONNECTED = 1,
        RESOURCE_GLOBALNET = 2,
        RESOURCE_REMEMBERED = 3,
        RESOURCE_RECENT = 4,
        RESOURCE_CONTEXT = 5
    }

    public enum RESOURCE_TYPE
    {
        RESOURCETYPE_ANY = 0,
        RESOURCETYPE_DISK = 1,
        RESOURCETYPE_PRINT = 2,
        RESOURCETYPE_RESERVED = 8,
    }

    public enum RESOURCE_USAGE
    {
        RESOURCEUSAGE_CONNECTABLE = 1,
        RESOURCEUSAGE_CONTAINER = 2,
        RESOURCEUSAGE_NOLOCALDEVICE = 4,
        RESOURCEUSAGE_SIBLING = 8,
        RESOURCEUSAGE_ATTACHED = 16,
        RESOURCEUSAGE_ALL = (RESOURCEUSAGE_CONNECTABLE | RESOURCEUSAGE_CONTAINER | RESOURCEUSAGE_ATTACHED),
    }

    public enum RESOURCE_DISPLAYTYPE
    {
        RESOURCEDISPLAYTYPE_GENERIC = 0,
        RESOURCEDISPLAYTYPE_DOMAIN = 1,
        RESOURCEDISPLAYTYPE_SERVER = 2,
        RESOURCEDISPLAYTYPE_SHARE = 3,
        RESOURCEDISPLAYTYPE_FILE = 4,
        RESOURCEDISPLAYTYPE_GROUP = 5,
        RESOURCEDISPLAYTYPE_NETWORK = 6,
        RESOURCEDISPLAYTYPE_ROOT = 7,
        RESOURCEDISPLAYTYPE_SHAREADMIN = 8,
        RESOURCEDISPLAYTYPE_DIRECTORY = 9,
        RESOURCEDISPLAYTYPE_TREE = 10,
        RESOURCEDISPLAYTYPE_NDSCONTAINER = 11
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct NETRESOURCE
    {
        public RESOURCE_SCOPE dwScope;
        public RESOURCE_TYPE dwType;
        public RESOURCE_DISPLAYTYPE dwDisplayType;
        public RESOURCE_USAGE dwUsage;

        [MarshalAs(UnmanagedType.LPStr)] public string lpLocalName;

        [MarshalAs(UnmanagedType.LPStr)] public string lpRemoteName;

        [MarshalAs(UnmanagedType.LPStr)] public string lpComment;

        [MarshalAs(UnmanagedType.LPStr)] public string lpProvider;
    }

    public class SharedTool
    {

        [DllImport("mpr.dll")]
        public static extern int WNetAddConnection2A(NETRESOURCE[] lpNetResource, string lpPassword, string lpUserName,
                                                     int dwFlags);

        [DllImport("mpr.dll")]
        public static extern int WNetCancelConnection2A(string sharename, int dwFlags, int fForce);

        [DllImport("Netapi32.dll")]
        public static extern int NetShareCheck(
            [MarshalAs(UnmanagedType.LPWStr)]string ServerName,
            [MarshalAs(UnmanagedType.LPWStr)]string Device,
            out long Type);

        public static int Connect(string remotePath, string localPath, string username, string password)
        {
            NETRESOURCE[] share_driver = new NETRESOURCE[1];
            share_driver[0].dwScope = RESOURCE_SCOPE.RESOURCE_GLOBALNET;
            share_driver[0].dwType = RESOURCE_TYPE.RESOURCETYPE_DISK;
            share_driver[0].dwDisplayType = RESOURCE_DISPLAYTYPE.RESOURCEDISPLAYTYPE_SHARE;
            share_driver[0].dwUsage = RESOURCE_USAGE.RESOURCEUSAGE_CONNECTABLE;
            share_driver[0].lpLocalName = localPath;
            share_driver[0].lpRemoteName = remotePath;

            Disconnect(localPath);
            int ret = WNetAddConnection2A(share_driver, password, username, 1);

            return ret;
        }

        public static int Disconnect(string localpath)
        {
            return WNetCancelConnection2A(localpath, 1, 1);
        }

        public static string ReadSharedText(FileInfo remotePath)
        {
            string serverName = remotePath.Directory.FullName;
            serverName=serverName.TrimStart(new char[] {'/', '\\'});
            int nextIndex = serverName.IndexOf('/');
            if (nextIndex==-1)
            {
                nextIndex = serverName.IndexOf('\\');
            }
            if (nextIndex>=0)
            {
                serverName = serverName.Substring(0, nextIndex);
            }

            if (!IsDriveReady(serverName))
            {
                return string.Empty;
            }

            if (remotePath.Exists)
            {
                return File.ReadAllText(remotePath.FullName);
            }
            return string.Empty;

            //string result = string.Empty;
            //string localpath = "X:";
            //int status = Connect(remotePath.Directory.FullName, localpath, @"test", "test");
            //if (status == (int) ERROR_ID.ERROR_SUCCESS)
            //{
            //    if (remotePath.Exists)
            //    {
            //        result = File.ReadAllText(remotePath.FullName);
            //    }
            //}
            //else
            //{
                
            //}

            //Disconnect(localpath);
            //return result;
        }

        private static  bool IsDriveReady(string serverName)
        {
            // ***  SET YOUR TIMEOUT HERE  ***     
            int timeout = 5;    // 5 seconds 
            System.Net.NetworkInformation.Ping pingSender = new System.Net.NetworkInformation.Ping();
            System.Net.NetworkInformation.PingOptions options = new System.Net.NetworkInformation.PingOptions();
            options.DontFragment = true;
            // Enter a valid ip address     
            string ipAddressOrHostName = serverName;
            string data = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
            byte[] buffer = System.Text.Encoding.ASCII.GetBytes(data);
            System.Net.NetworkInformation.PingReply reply = pingSender.Send(ipAddressOrHostName, timeout, buffer, options);
            return (reply.Status == System.Net.NetworkInformation.IPStatus.Success);
        }

        public static void TestNetWorkConnection()
        {
            string localpath = "X:";
            int status = SharedTool.Connect("////192.168.0.2//test", localpath, @"test", "test");
            if (status == (int) ERROR_ID.ERROR_SUCCESS)
            {
                FileStream fs = new FileStream(localpath + @"//123.txt", FileMode.OpenOrCreate);
                using (StreamWriter stream = new StreamWriter(fs))
                {
                    stream.WriteLine("???????");
                    stream.Flush();
                    stream.Close();
                }
                fs.Close();
            }
            else
            {
                Console.WriteLine(status);
            }
            SharedTool.Disconnect(localpath);
        }

       
    }
}