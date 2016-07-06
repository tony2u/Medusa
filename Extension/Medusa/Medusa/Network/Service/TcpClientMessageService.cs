using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Net;
using System.Net.Sockets;
using System.Reflection.Emit;
using System.Text;
using System.Threading;
using Medusa.Log;
using Medusa.Network.Message;

namespace Medusa.Network.Service
{
    public class TcpClientMessageService : IDisposable
    {
        private static uint mMessageVersion = 0;

        private readonly NetworkBuffer mReadBuffer = new NetworkBuffer();
        private readonly NetworkBuffer mWriteBuffer = new NetworkBuffer();
        private readonly Dictionary<uint, IMessage> mMessages = new Dictionary<uint, IMessage>();
        private TcpClient mTcpClient;
        private bool mDisposed;
        private int mRetries;
        private readonly Stopwatch mHeartbeatWatch = new Stopwatch();
        public bool Connected => mTcpClient != null && mTcpClient.Connected;

        public IPAddress[] Addresses { get; }
        public int Port { get; }
        public int ConnectRetries { get; set; }
        public int ConnectRetryInterval { get; set; }
        public uint HeartbeatMilliseconds { get; set; }

        public IPEndPoint RemoteIPEndPoint => new IPEndPoint(Addresses[0], Port);

        protected IPEndPoint LocalIPEndPoint { get; }
        public Encoding Encoding { get; set; }
        public event EventHandler<TcpClientEventArgs> OnConnected;
        public event EventHandler<TcpClientEventArgs> OnDisconnected;
        public event EventHandler<TcpClientExceptionEventArgs> OnError;
        public event EventHandler<TcpClientDataEventArgs<NetworkBuffer>> OnRead;

        public TcpClientMessageService(IPEndPoint remoteEndPoint)
          : this(new[] { remoteEndPoint.Address }, remoteEndPoint.Port)
        {
        }

        public TcpClientMessageService(IPEndPoint remoteEndPoint, IPEndPoint localEndPoint)
          : this(new[] { remoteEndPoint.Address }, remoteEndPoint.Port, localEndPoint)
        {
        }

        public TcpClientMessageService(IPAddress remoteIP, int remotePort)
          : this(new[] { remoteIP }, remotePort)
        {
        }

        public TcpClientMessageService(IPAddress remoteIPAddress, int remotePort, IPEndPoint localEndPoint)
          : this(new[] { remoteIPAddress }, remotePort, localEndPoint)
        {
        }

        public TcpClientMessageService(string remoteHostName, int remotePort)
          : this(Dns.GetHostAddresses(remoteHostName), remotePort)
        {
        }

        public TcpClientMessageService(string remoteHostName, int remotePort, IPEndPoint localEndPoint)
          : this(Dns.GetHostAddresses(remoteHostName), remotePort, localEndPoint)
        {
        }

        public TcpClientMessageService(IPAddress[] remoteIPAddresses, int remotePort)
          : this(remoteIPAddresses, remotePort, null)
        {
        }

        public TcpClientMessageService(IPAddress[] remoteIPAddresses, int remotePort, IPEndPoint localEndPoint)
        {
            Addresses = remoteIPAddresses;
            Port = remotePort;
            LocalIPEndPoint = localEndPoint;
            Encoding = Encoding.UTF8;


            ConnectRetries = 3;
            ConnectRetryInterval = 5;
        }

        protected void OnResetBuffer()
        {
            mReadBuffer.RetrieveAll();
            mWriteBuffer.RetrieveAll();
        }

        protected void OnHandleConnected()
        {
            OnConnected?.Invoke(this, new TcpClientEventArgs(mTcpClient));
        }

        protected void OnHandleDisconnected()
        {
            OnResetBuffer();
            OnDisconnected?.Invoke(this, new TcpClientEventArgs(mTcpClient));
            BeginConnect();
        }

        protected void OnHandleError(Exception e)
        {
            OnError?.Invoke(this, new TcpClientExceptionEventArgs(mTcpClient, e));

        }

        protected void OnHandleRead()
        {
            mHeartbeatWatch.Start();
            OnRead?.Invoke(this, new TcpClientDataEventArgs<NetworkBuffer>(mTcpClient, mReadBuffer));
            if (mReadBuffer.ReadableCount >= 4)
            {
                uint size = mReadBuffer.PeekUInt();
                if (size <= mReadBuffer.ReadableCount - 4)
                {
                    mReadBuffer.Retrieve(4);
                    uint fromServiceId = mReadBuffer.ReadUInt();
                    uint toServiceId = mReadBuffer.ReadUInt();
                    uint version = mReadBuffer.ReadUInt();
                    uint id = mReadBuffer.ReadUInt();
                    uint sessionId = mReadBuffer.ReadUInt();
                    uint connectionId = mReadBuffer.ReadUInt();

                    var data = mReadBuffer.ReadData((int)size - 4 * 6);
                    if (id != 0)
                    {
                        //request from client
                        IMessage message = MessageFactory.Create(id);
                        if (message != null)
                        {
                            message.FromService = fromServiceId;
                            message.ToService = toServiceId;
                            message.Version = version;
                            message.Id = id;
                            message.SessionId = sessionId;
                            message.ConnectionId = connectionId;
                            message.DeserializeRequest(new ArraySegment<byte>(data));
                            message.OnRequest(this);

                            //resend back
                            if (message.SessionId != 0)
                            {
                                uint temp = message.FromService;
                                message.FromService = message.ToService;
                                message.ToService = temp;
                                message.Id = 0; //indicate response
                                Write(message);
                            }
                        }
                        else
                        {
                            Logger.ErrorLine("Invalid message id:{0}", id);
                        }

                    }
                    else
                    {
                        //response from server
                        if (sessionId != 0)
                        {
                            IMessage outPrevMessage;
                            if (mMessages.TryGetValue(sessionId, out outPrevMessage))
                            {
                                mMessages.Remove(sessionId);
                                outPrevMessage.Id = 0;  //indicate a response
                                outPrevMessage.DeserializeResponse(new ArraySegment<byte>(data));
                                outPrevMessage.OnResponse(this);
                            }
                            else
                            {
                                Logger.ErrorLine("Error: Got a response after timeout.id:{0} sessionId:{1}", id, sessionId);

                            }
                        }
                        else
                        {
                            Logger.ErrorLine("Error: ResponseMessage from server must have a session id");
                        }

                    }

                }
            }

        }

        protected byte[] OnHandleWrite(IMessage message)
        {
            mHeartbeatWatch.Start();

            if (message.SessionId != 0)
            {
                mMessages.Add(message.SessionId, message);
            }

            message.Version = mMessageVersion;
            message.OnSend(this);

            ArraySegment<byte>? data;
            if (message.IsRequest)
            {
                data = message.SerializeRequest();
            }
            else
            {
                data = message.SerializeResponse();
            }

            int totalSize = (data?.Count ?? 0) + 4 * 6;
            mWriteBuffer.Write(totalSize);
            mWriteBuffer.Write(message.FromService);
            mWriteBuffer.Write(message.ToService);
            mWriteBuffer.Write(message.Version);
            mWriteBuffer.Write(message.Id);
            mWriteBuffer.Write(message.SessionId);
            mWriteBuffer.Write(message.ConnectionId);
            if (data != null)
            {
                mWriteBuffer.Write(data.Value.Array, data.Value.Offset, data.Value.Count);
            }

            return mWriteBuffer.ReadAll();
        }

        public TcpClientMessageService BeginConnect()
        {
            if (!Connected)
            {
                mTcpClient = LocalIPEndPoint != null ? new TcpClient(LocalIPEndPoint) : new TcpClient();
                mTcpClient.BeginConnect(Addresses, Port, OnConnectResult, mTcpClient);
            }

            return this;
        }

        private void OnConnectResult(IAsyncResult ar)
        {
            try
            {
                mTcpClient.EndConnect(ar);
                OnHandleConnected();
                mRetries = 0;
                StartHeartbeat();
            }
            catch (Exception ex)
            {
                if (mRetries > 0)
                {
                    Logger.InfoLine(string.Format(CultureInfo.InvariantCulture,
                      "BeginConnect to server with retry {0} failed.", mRetries));
                }

                mRetries++;
                if (mRetries > ConnectRetries)
                {
                    // we have failed to connect to all the IP Addresses, 
                    // connection has failed overall.
                    OnHandleError(ex);
                    return;
                }

                Logger.InfoLine(string.Format(CultureInfo.InvariantCulture,
                    "Waiting {0} seconds before retrying to connect to server.",
                    ConnectRetryInterval));
                Thread.Sleep(TimeSpan.FromSeconds(ConnectRetryInterval));
                BeginConnect();
                return;
            }

            // we are connected successfully and start asyn read operation.
            byte[] buffer = new byte[mTcpClient.ReceiveBufferSize];
            mTcpClient.GetStream().BeginRead(buffer, 0, buffer.Length, OnReadResult, buffer);
        }

        public TcpClientMessageService Close()
        {
            if (Connected)
            {
                mHeartbeatWatch.Stop();
                mRetries = 0;
                mTcpClient.Close();
                OnHandleDisconnected();
            }

            return this;
        }

        private void OnReadResult(IAsyncResult ar)
        {
            NetworkStream stream = mTcpClient.GetStream();

            int numberOfReadBytes;
            try
            {
                numberOfReadBytes = stream.EndRead(ar);
            }
            catch
            {
                numberOfReadBytes = 0;
            }

            if (numberOfReadBytes == 0)
            {
                // connection has been closed
                Close();
                return;
            }

            // received byte and trigger event notification
            byte[] buffer = (byte[])ar.AsyncState;
            mReadBuffer.Write(buffer, 0, numberOfReadBytes);
            try
            {
                OnHandleRead();
            }
            catch (Exception e)
            {
                Logger.ErrorLine(e.Message);
            }
            stream.BeginRead(buffer, 0, buffer.Length, OnReadResult, buffer);
        }

        public void Write(IMessage message)
        {
            if (message == null)
                throw new ArgumentNullException(nameof(message));

            if (!Connected)
            {
                OnResetBuffer();
                OnDisconnected?.Invoke(this, new TcpClientEventArgs(mTcpClient));
                throw new InvalidProgramException(
                  "This client has not connected to server.");
            }

            try
            {
                var buffer = OnHandleWrite(message);
                mTcpClient.GetStream().BeginWrite(buffer, 0, buffer.Length, OnWriteResult, mTcpClient);
            }
            catch (Exception e)
            {
                Logger.ErrorLine(e.Message);
            }
        }

        private void OnWriteResult(IAsyncResult ar)
        {
            ((TcpClient)ar.AsyncState).GetStream().EndWrite(ar);
        }

        public void StartHeartbeat()
        {
            if (HeartbeatMilliseconds!=0)
            {
                mHeartbeatWatch.Start();
                ThreadPool.QueueUserWorkItem(OnHeartbeat, this);
            }
          
        }

        private void OnHeartbeat(object state)
        {
            while (Connected)
            {
                if (HeartbeatMilliseconds != 0)
                {
                    if (mHeartbeatWatch.ElapsedMilliseconds > HeartbeatMilliseconds)
                    {
                        Write(new HeartbeatMessage());
                        mHeartbeatWatch.Reset();
                        mHeartbeatWatch.Start();
                    }
                }
            }
           
        }

        #region IDisposable Members

        /// <summary>
        /// Performs application-defined tasks associated with freeing, 
        /// releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed 
        /// and unmanaged resources; <c>false</c> 
        /// to release only unmanaged resources.
        /// </param>
        protected virtual void Dispose(bool disposing)
        {
            if (!this.mDisposed)
            {
                if (disposing)
                {
                    Close();
                    mTcpClient = null;
                }

                mDisposed = true;
            }
        }

        #endregion
    }
}
