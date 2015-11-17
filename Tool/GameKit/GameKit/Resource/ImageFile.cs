// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;
using System.Text;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using GameKit.Log;
using GameKit.Publish;
using Color = System.Drawing.Color;
using PixelFormat = System.Drawing.Imaging.PixelFormat;

namespace GameKit.Resource
{
    public class ImageFile : FileListFile, IComparable<ImageFile>
    {
        public ImageFile(FileInfo filePath, bool enablePacking = true,bool isCoded=false)
            : base(filePath, enablePacking,isCoded)
        {
            if (filePath.Exists)
            {
                OriginalSize = GetImageSize(filePath);
                ResultSize = OriginalSize;
            }

            IsOptimzed = true;
        }

        public static Size GetImageSize(FileInfo filePath)
        {
            if (filePath.Name.EndsWith(".png"))
            {
                var buff = new byte[32];
                using (var d = filePath.OpenRead())
                {
                    d.Read(buff, 0, 32);
                }
                const int wOff = 16;
                const int hOff = 20;
                var Width = BitConverter.ToInt32(new[] { buff[wOff + 3], buff[wOff + 2], buff[wOff + 1], buff[wOff + 0], }, 0);
                var Height = BitConverter.ToInt32(new[] { buff[hOff + 3], buff[hOff + 2], buff[hOff + 1], buff[hOff + 0], }, 0);
                return new Size(Width, Height);
            }
            else
            {
                GC.Collect();
                var tempImage = (Bitmap)Bitmap.FromFile(filePath.FullName);
                Size size = tempImage.Size;
                tempImage.Dispose();
                return size;
            }


        }

        public Bitmap ResultImage
        {
            get;
            set;
        }
        public Rectangle? TextureRect { get; set; }
        public Point? Offset { get; set; }
        public bool IsOptimzed { get; set; }
        public Size OriginalSize { get; private set; }
        public Size ResultSize { get; set; }



        public int CompareTo(ImageFile other)
        {
            int widthDiff = other.ResultSize.Width - ResultSize.Width;
            if (widthDiff != 0)
            {
                return widthDiff;
            }
            return other.ResultSize.Height - ResultSize.Height;
        }

        void ConvertTo8bpp(Bitmap sourceBitmap, string outputFileName)
        {
            int width = sourceBitmap.Width;
            int height = sourceBitmap.Height;
            int stride = sourceBitmap.Width;

            // generate a custom palette for the bitmap (I already had a list of colors
            // from a previous operation
            Dictionary<System.Drawing.Color, byte> colorDict = new Dictionary<System.Drawing.Color, byte>(); // lookup table for conversion to indexed color
            List<System.Windows.Media.Color> colorList = new List<System.Windows.Media.Color>(); // list for palette creation
            byte index = 0;
            for (int x = 0; x < width; ++x)
            {
                for (int y = 0; y < height; ++y)
                {
                    var pixelColor = sourceBitmap.GetPixel(x, y);
                    if (!colorDict.ContainsKey(pixelColor))
                    {
                        colorDict.Add(pixelColor, index++);
                        System.Windows.Media.Color mediaColor = new System.Windows.Media.Color();
                        mediaColor.A = pixelColor.A;
                        mediaColor.R = pixelColor.R;
                        mediaColor.G = pixelColor.G;
                        mediaColor.B = pixelColor.B;

                        colorList.Add(mediaColor);
                    }
                }
            }


            // create the byte array of raw image data

            byte[] imageData = new byte[width * height];

            for (int x = 0; x < width; ++x)
            {
                for (int y = 0; y < height; ++y)
                {
                    var pixelColor = sourceBitmap.GetPixel(x, y);
                    imageData[x + (stride * y)] = colorDict[pixelColor];
                }
            }

            System.Windows.Media.Imaging.BitmapPalette bmpPal = new System.Windows.Media.Imaging.BitmapPalette(colorList);

            // generate the image source
            var bsource = BitmapSource.Create(width, height, 96, 96, PixelFormats.Indexed8, bmpPal, imageData, stride);

            // encode the image
            PngBitmapEncoder encoder = new PngBitmapEncoder();
            encoder.Interlace = PngInterlaceOption.On;
            encoder.Frames.Add(BitmapFrame.Create(bsource));

            using (var stream = new FileStream(outputFileName, FileMode.Create))
            {
                encoder.Save(stream);
            }
        }

        public void Save()
        {
            //ConvertTo8bpp(ResultImage, FileInfo.FullName);
            if (IsOptimzed)
            {
                ResultImage.Save(FileInfo.FullName, ImageFormat.Png);
            }

        }

        private Bitmap ChangePixelFormat(Bitmap inputImage, PixelFormat newFormat)
        {
            Bitmap bmp = new Bitmap(inputImage.Width, inputImage.Height, newFormat);
            using (Graphics g = Graphics.FromImage(bmp))
            {
                g.DrawImage(inputImage, 0, 0);
            }
            return bmp;
        }



        public override string ToString()
        {
            var sb = new StringBuilder();
            bool isAdd = false;

            if (PublishGroup != null)
            {
                isAdd = true;
                sb.Append(PublishGroup);
            }

            //if (ResultFile != null && !ReferenceEquals(ResultFile, OriginalFile))
            //{
            //    if (isAdd)
            //    {
            //        sb.Append("\t");
            //    }
            //    sb.Append(ResultFile.FileInfo.Name);
            //    isAdd = true;

            //}

            if (!OriginalSize.IsEmpty && ResultImage != null)
            {
                if (isAdd)
                {
                    sb.Append("\t");
                }
                sb.AppendFormat("{0}=>{1}", OriginalSize, ResultImage.Size);
                isAdd = true;

            }

            if (TextureRect.HasValue)
            {
                if (isAdd)
                {
                    sb.Append("\t");
                }
                sb.Append(TextureRect.ToString());
                isAdd = true;

            }

            if (Offset.HasValue)
            {
                if (isAdd)
                {
                    sb.Append("\t");
                }
                sb.Append(Offset.ToString());

            }


            return sb.ToString();
        }

        public void Optimze()
        {
            if (!IsOptimzed)
            {
                return;
            }

            if (PublishTarget.Current.IsCacheEnabled && FileCacheCenter.IsInCache(FileInfo,Md5,FileCacheOperation.ImageOptimzed))
            {
                var fileInfo = FileCacheCenter.GetCacheFileInfo(FileInfo,Md5,FileCacheOperation.ImageOptimzed);
                var cacheItem = FileCacheCenter.GetCacheFileItem(FileInfo,Md5,FileCacheOperation.ImageOptimzed);

                if (ResultImage!=null)
                {
                    ResultImage.Dispose();
                    GC.Collect();
                    ResultImage = null;
                }

                
                //ResultImage = (Bitmap)Bitmap.FromFile(fileInfo.FullName);
                ResultSize = GetImageSize(fileInfo);

                if (cacheItem.TextureRect != null)
                {
                    Rectangle rect=new Rectangle();
                    rect.X = (int)cacheItem.TextureRect.Origin.X;
                    rect.Y = (int)cacheItem.TextureRect.Origin.Y;
                    rect.Width = (int) cacheItem.TextureRect.Size.Width;
                    rect.Height = (int)cacheItem.TextureRect.Size.Height;
                    TextureRect = rect;
                }

                if (cacheItem.Offset!=null)
                {
                    Point pos=new Point();
                    pos.X = (int) cacheItem.Offset.X;
                    pos.Y = (int)cacheItem.Offset.Y;

                    Offset = pos;
                }

                Logger.LogInfoLine("FileCache Hit:Optimze {0} ", FileInfo.FullName);
                UpdateFileInfo(fileInfo);
            }
            else
            {
                var originalImage = (Bitmap)Bitmap.FromFile(FileInfo.FullName);

                var leftBottom = new Point(int.MaxValue, int.MaxValue);
                var rightTop = Point.Empty;

                bool isBreak = false;
                for (int i = 0; i < originalImage.Width; i++)
                {
                    for (int j = 0; j < originalImage.Height; j++)
                    {
                        var color = originalImage.GetPixel(i, j);
                        if (color.A != 0)
                        {
                            leftBottom.X = i;
                            isBreak = true;
                            break;
                        }
                    }
                    if (isBreak)
                    {
                        break;
                    }
                }

                isBreak = false;
                for (int i = originalImage.Width - 1; i >= 0; i--)
                {
                    for (int j = 0; j < originalImage.Height; j++)
                    {
                        var color = originalImage.GetPixel(i, j);
                        if (color.A != 0)
                        {
                            rightTop.X = i;
                            isBreak = true;
                            break;
                        }
                    }
                    if (isBreak)
                    {
                        break;
                    }
                }

                isBreak = false;
                for (int i = 0; i < originalImage.Height; i++)
                {
                    for (int j = 0; j < originalImage.Width; j++)
                    {
                        var color = originalImage.GetPixel(j, i);
                        if (color.A != 0)
                        {
                            leftBottom.Y = i;
                            isBreak = true;
                            break;
                        }
                    }
                    if (isBreak)
                    {
                        break;
                    }
                }

                isBreak = false;
                for (int i = originalImage.Height - 1; i >= 0; i--)
                {
                    for (int j = 0; j < originalImage.Width; j++)
                    {
                        var color = originalImage.GetPixel(j, i);
                        if (color.A != 0)
                        {
                            rightTop.Y = i;
                            isBreak = true;
                            break;
                        }
                    }
                    if (isBreak)
                    {
                        break;
                    }
                }

                var clipRect = new Rectangle(leftBottom,
                    new Size(rightTop.X - leftBottom.X + 1, rightTop.Y - leftBottom.Y + 1));
                if (leftBottom.X == int.MaxValue || leftBottom.Y == int.MaxValue)
                {
                    ResultImage = originalImage;

                    Logger.LogError("Empty image:{0}\r\n", FileInfo);
                }
                else
                {
                    if (clipRect.Size != originalImage.Size)
                    {
                        Offset = new Point(leftBottom.X, originalImage.Size.Height - clipRect.Bottom);
                        ResultImage = ClipImage(originalImage, clipRect);
                        originalImage.Dispose();
                        ResultSize = ResultImage.Size;
                    }
                    else
                    {
                        ResultImage = originalImage;
                    }
                }

                if (PublishTarget.Current.IsCacheEnabled)
                {
                    var newFileInfo = FileCacheCenter.GetCacheNewFileInfo(FileInfo.FullName, FileCacheOperation.ImageOptimzed);
                    if (newFileInfo.Exists)
                    {
                        newFileInfo.Delete();
                    }
                    ResultImage.Save(newFileInfo.FullName, ImageFormat.Png);
                    FileCacheCenter.AddToCacheWithoutCopy(Md5, FileInfo,TextureRect,Offset,FileCacheOperation.ImageOptimzed);

                    UpdateFileInfo(newFileInfo);
                }
                else
                {
                    UpdateFileInfo(FileInfo);
                }

                ResultImage.Dispose();
                GC.Collect();
                ResultImage = null;

                
            }

            //Logger.LogInfoLine("Optimze image:{0}", ToString());
        }

        private Bitmap ClipImage(Bitmap image, Rectangle clipRect)
        {
            var resultImage = new Bitmap(clipRect.Width, clipRect.Height);

            using (var graphics = Graphics.FromImage(resultImage))
            {
                graphics.Clear(Color.Transparent);
                graphics.CompositingQuality = CompositingQuality.HighQuality;
                graphics.SmoothingMode = SmoothingMode.HighQuality;
                graphics.InterpolationMode = InterpolationMode.HighQualityBicubic;

                var toRect = new Rectangle(0, 0, clipRect.Width, clipRect.Height);
                graphics.DrawImage(image, toRect, clipRect, GraphicsUnit.Pixel);
            }


            return resultImage;
        }

        public static bool IsPOTSize(int val)
        {
            return (val & (val - 1)) == 0;
        }


        public string TryConvertSelfToPVR()
        {
            if (PublishTarget.Current.IsPVR && IsPVREnabled)
            {
                if (!IsPOTSize(ResultSize.Width) || !IsPOTSize(ResultSize.Height))
                {
                    Logger.LogAllLine("NOT POT image size :{0}-{1} of {2}", ResultSize.Width, ResultSize.Height, FileInfo);
                    return FileInfo.FullName;
                }

                string newFilePath = TryConvertToPVR(FileInfo, Md5);
                UpdateFileInfo(new FileInfo(newFilePath));
                return newFilePath;

            }
            return FileInfo.FullName;

        }

        public static string TryConvertToPVR(FileInfo filePath, string md5)
        {
            if (!PublishTarget.Current.IsPVR)
            {
                return filePath.FullName;
            }

            string outFilePath = filePath.FullName;
            outFilePath = outFilePath.Replace(filePath.Extension, ".pvr");

            if (PublishTarget.Current.IsCacheEnabled && FileCacheCenter.IsInCache(new FileInfo(outFilePath), md5, FileCacheOperation.PVR))
            {
                outFilePath = FileCacheCenter.CopyCacheToDirectory(new FileInfo(outFilePath), md5, filePath.Directory, FileCacheOperation.PVR);
                Logger.LogInfoLine("FileCache Hit:TryConvertToPVR {0} ", filePath.FullName);
                filePath.Delete();  //delete original file

                return outFilePath;
            }
            else
            {
                string arguments = string.Format("-i {0} -o {1} -f {2} -q {3}", filePath.FullName, outFilePath,
                    PublishTarget.Current.PVRFormat, PublishTarget.Current.PVRQuality.ToString());

                ProcessStartInfo start = new ProcessStartInfo("PVRTexToolCLI.exe");
                Logger.LogInfoLine("PVRTexToolCLI.exe {0} {1}", filePath.FullName, outFilePath);
                start.Arguments = arguments;//??????

                start.CreateNoWindow = true;//???dos?????
                start.RedirectStandardOutput = true;//
                start.RedirectStandardInput = true;//
                start.UseShellExecute = false;//????????????????
                Process p = Process.Start(start);
                StreamReader reader = p.StandardOutput;//?????
                do
                {
                    string line = reader.ReadLine();//??????
                    if (!string.IsNullOrEmpty(line))
                    {
                        Logger.LogInfoLine(line);
                    }

                } while (!reader.EndOfStream);

                p.WaitForExit();//???????????
                p.Close();//????
                reader.Close();//???
                filePath.Delete();  //delete original file

                if (PublishTarget.Current.IsCacheEnabled)
                {
                    FileCacheCenter.AddToCache(md5, new FileInfo(outFilePath), FileCacheOperation.PVR);
                }

                return outFilePath;
            }


        }
    }
}