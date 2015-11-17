// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Drawing;
using System.Linq;
using GameKit.Common;
using GameKit.Log;
using GameKit.Resource;

namespace GameKit.Packing
{
    internal enum ImageFitType
    {
        Fit,
        FitEqual,
        TooBigWidth,
        TooBigHeight
    }

    internal enum FreeLineMergeType
    {
        Left,
        Right,
        Error
    }

    internal enum FreeLineAttachType
    {
        Left,
        Right,
        Error
    }

    internal class LayoutFreeLine : IComparable<LayoutFreeLine>
    {
        public LayoutFreeLine(int y, int beginX, int endX)
        {
            Y = y;
            BeginX = beginX;
            EndX = endX;
        }

        public int Y { get; set; }
        public int BeginX { get; set; }
        public int EndX { get; set; }

        public int Width
        {
            get { return EndX - BeginX; }
        }

        public Point Location
        {
            get { return new Point(BeginX, Y); }
        }

        public int CompareTo(LayoutFreeLine other)
        {
            int yDiff = Y - other.Y;
            if (yDiff != 0)
            {
                return yDiff;
            }
            return BeginX - other.BeginX;
        }

        public override string ToString()
        {
            return string.Format("{0}:{1}-{2}", Y, BeginX, EndX);
        }

        public FreeLineMergeType GetMergeType(LayoutFreeLine other)
        {
            if (Y == other.Y)
            {
                if (BeginX == other.EndX + 1)
                {
                    return FreeLineMergeType.Left;
                }

                if (EndX + 1 == other.BeginX)
                {
                    return FreeLineMergeType.Right;
                }
            }

            return FreeLineMergeType.Error;
        }

        public FreeLineAttachType GetAttachType(LayoutFreeLine other)
        {
            if (BeginX == other.EndX + 1)
            {
                return FreeLineAttachType.Left;
            }
            if (EndX + 1 == other.BeginX)
            {
                return FreeLineAttachType.Right;
            }

            return FreeLineAttachType.Error;
        }

        public ImageFitType GetFitType(ImageFile image, Size maxImageSize)
        {
            if (image.ResultSize.Height + Y > maxImageSize.Height)
            {
                return ImageFitType.TooBigHeight;
            }

            if (image.ResultSize.Width > Width)
            {
                return ImageFitType.TooBigWidth;
            }

            if (image.ResultSize.Width == Width)
            {
                return ImageFitType.FitEqual;
            }
            return ImageFitType.Fit;
        }

        public LayoutFreeLine NewMergeLine(LayoutFreeLine otherLine, FreeLineMergeType mergeType)
        {
            switch (mergeType)
            {
                case FreeLineMergeType.Right:
                    return new LayoutFreeLine(Y, BeginX, otherLine.EndX);
                case FreeLineMergeType.Left:
                    return new LayoutFreeLine(Y, otherLine.BeginX, EndX);
                default:
                    return null;
            }
        }

        public LayoutFreeLine NewAttachLine(LayoutFreeLine otherLine, FreeLineAttachType attachType)
        {
            switch (attachType)
            {
                case FreeLineAttachType.Right:
                    return new LayoutFreeLine(otherLine.Y, BeginX, otherLine.EndX);
                case FreeLineAttachType.Left:
                    return new LayoutFreeLine(otherLine.Y, otherLine.BeginX, EndX);
                default:
                    return null;
            }
        }


        public LayoutFreeLine NewImageLineAfterFit(ImageFile image)
        {
            return new LayoutFreeLine(image.ResultSize.Height + Y + 1, BeginX, BeginX + image.ResultSize.Width);
        }

        public LayoutFreeLine NewCurrentLineAfterFit(ImageFile image)
        {
            return new LayoutFreeLine(Y, BeginX + image.ResultSize.Width + 1, EndX);
        }
    }

    public class ImageLayouter
    {
        private readonly MySortedList<LayoutFreeLine> mFreeLines = new MySortedList<LayoutFreeLine>();
        private Size mCurrentMaxImageSize;
        private Size mResultImageSize;

        private Size mLimitMaxImageSize;

        private readonly bool mIsPOT;
        private readonly bool mIsSquare;


        public ImageLayouter(Size defaultImageSize,Size maxImageSize,bool isPOT,bool isSquare)
        {
            UsedImages = new MySortedList<ImageFile>();
            mCurrentMaxImageSize = defaultImageSize;
            mLimitMaxImageSize = maxImageSize;

            mResultImageSize.Width = 0;
            mResultImageSize.Height = 0;
            mIsPOT = isPOT;
            mIsSquare = isSquare;

            
        }

        public Size ResultImageFixedSize { get; private set; }

        public MySortedList<ImageFile> UsedImages { get; private set; }

        public void Generate(MySortedList<ImageFile> images)
        {
            foreach (var imageFile in images)
            {
                if (imageFile.ResultSize.Width > mLimitMaxImageSize.Width ||
                    imageFile.ResultSize.Height > mLimitMaxImageSize.Height)
                {
                    UsedImages.Add(imageFile);
                    return;
                }
            }

            MySortedList<ImageFile> imagesCopy = new MySortedList<ImageFile>();

            do
            {
                imagesCopy.Clear();
                imagesCopy.AddRange(images);
                mResultImageSize.Width = 0;
                mResultImageSize.Height = 0;

                UsedImages.Clear();
                //init fist free line
                var firstLine = new LayoutFreeLine(0, 0, mCurrentMaxImageSize.Width);
                mFreeLines.Add(firstLine);
                Run(imagesCopy);

                Logger.LogInfoLine("Try Layout: All:{0}?Used:{1}  ({2},{3})", images.Count, UsedImages.Count, mCurrentMaxImageSize.Width, mCurrentMaxImageSize.Height);

                if (imagesCopy.Count==0&&UsedImages.Count==images.Count)
                {
                    break;
                }
                else
                {
                    int nextSize = ccNextPOT(mCurrentMaxImageSize.Width+1);
                    if (nextSize>mLimitMaxImageSize.Width)
                    {
                        break;
                    }
                    mCurrentMaxImageSize = new Size(nextSize, nextSize);
                }

                mFreeLines.Clear();

            } while (true);
           

            //
            CalculateResultImageSize();

            //end
            images.Clear();
            images.AddRange(imagesCopy);
        }

        public void Run(MySortedList<ImageFile> images)
        {
            int lineIndex = 0;
            var currentImage = images.First;
            var currentLine = mFreeLines[lineIndex];

            while (images.Count > 0)
            {
                var fitType = currentLine.GetFitType(currentImage, mCurrentMaxImageSize);
                switch (fitType)
                {
                    case ImageFitType.FitEqual:
                        {
                            var newLine = currentLine.NewImageLineAfterFit(currentImage);
                            mFreeLines.Remove(currentLine);
                            mFreeLines.Add(newLine); //try to merge
                            //MergeLines(newLine);

                            images.Remove(currentImage);
                            currentImage.TextureRect = new Rectangle(currentLine.Location, currentImage.ResultSize);
                            mResultImageSize.Height = Math.Max(mResultImageSize.Height,
                                                               currentImage.TextureRect.Value.Bottom);
                            mResultImageSize.Width = Math.Max(mResultImageSize.Width,
                                                              currentImage.TextureRect.Value.Right);


                            UsedImages.Add(currentImage);
                            if (images.Count == 0)
                            {
                                return;
                            }
                            currentImage = images.First;
                            currentLine = mFreeLines[lineIndex];
                            lineIndex = 0;
                        }

                        break;
                    case ImageFitType.Fit:
                        {
                            var newImageLine = currentLine.NewImageLineAfterFit(currentImage);
                            var newCurrentLine = currentLine.NewCurrentLineAfterFit(currentImage);
                            mFreeLines.Remove(currentLine);
                            mFreeLines.Add(newImageLine); //try to merge  
                            mFreeLines.Add(newCurrentLine);
                            MergeLines(newImageLine);

                            images.Remove(currentImage);
                            currentImage.TextureRect = new Rectangle(currentLine.Location, currentImage.ResultSize);
                            mResultImageSize.Height = Math.Max(mResultImageSize.Height,
                                                               currentImage.TextureRect.Value.Bottom);
                            mResultImageSize.Width = Math.Max(mResultImageSize.Width,
                                                              currentImage.TextureRect.Value.Right);
                            UsedImages.Add(currentImage);
                            if (images.Count == 0)
                            {
                                return;
                            }

                            currentImage = images.First;
                            currentLine = mFreeLines[lineIndex];
                            lineIndex = 0;
                        }
                        break;
                    case ImageFitType.TooBigHeight:
                        {
                            images.Remove(currentImage);
                            if (images.Count == 0)
                            {
                                return;
                            }

                            currentImage = images.First;
                        }
                        break;
                    case ImageFitType.TooBigWidth:
                        {
                            ImageFile nextImage = (from imageFile in images let newFitType = currentLine.GetFitType(imageFile, mCurrentMaxImageSize) where newFitType == ImageFitType.FitEqual || newFitType == ImageFitType.Fit select imageFile).FirstOrDefault();

                            if (nextImage != null)
                            {
                                images.Remove(nextImage);

                                currentImage = nextImage;
                            }
                            else
                            {
                                if (AttachToLine(currentLine))
                                {
                                    lineIndex = 0;
                                    currentLine = mFreeLines[lineIndex];
                                }
                                else
                                {
                                    //merge to next line

                                    if (lineIndex == mFreeLines.Count - 1)
                                    {
                                        //cannot find to fit
                                        return;
                                    }
                                    ++lineIndex;
                                    currentLine = mFreeLines[lineIndex];
                                }
                            }
                        }
                        break;
                }
            }
        }
        private int ccNextPOT(int x)
        {
            x = x - 1;
            x = x | (x >> 1);
            x = x | (x >> 2);
            x = x | (x >> 4);
            x = x | (x >> 8);
            x = x | (x >> 16);
            return x + 1;
        }

        public void CalculateResultImageSize()
        {
            if (mIsPOT)
            {
                int width = ccNextPOT(mResultImageSize.Width);
                int height = ccNextPOT(mResultImageSize.Height);

                if (width > mLimitMaxImageSize.Width || height > mLimitMaxImageSize.Height)
                {
                    ResultImageFixedSize = mResultImageSize;
                }
                else
                {
                    ResultImageFixedSize = new Size(width, height);
                }

                if (mIsSquare)
                {
                    if (ResultImageFixedSize.Width != ResultImageFixedSize.Height)
                    {
                        int maxSize = Math.Max(ResultImageFixedSize.Width, ResultImageFixedSize.Height);
                        ResultImageFixedSize = new Size(maxSize, maxSize);
                    }
                }
            }
            else
            {
                ResultImageFixedSize = mResultImageSize;
            }

           
        }

        private void MergeLines(LayoutFreeLine newImageLine)
        {
            int index = mFreeLines.IndexOf(newImageLine);
            if (index < 0)
            {
                return;
            }

            for (int i = index + 1; i < mFreeLines.Count; i++)
            {
                var curLine = mFreeLines[i];
                var mergeType = newImageLine.GetMergeType(curLine);

                if (mergeType != FreeLineMergeType.Error)
                {
                    var newMergeLine = newImageLine.NewMergeLine(curLine, mergeType);
                    mFreeLines.Remove(newImageLine);
                    mFreeLines.Remove(curLine);
                    mFreeLines.Add(newMergeLine);
                }
            }
        }

        private bool AttachToLine(LayoutFreeLine currentLine)
        {
            int index = mFreeLines.IndexOf(currentLine);
            if (index < 0)
            {
                return false;
            }

            for (int i = index + 1; i < mFreeLines.Count; i++)
            {
                var curLine = mFreeLines[i];
                var attachType = currentLine.GetAttachType(curLine);

                if (attachType != FreeLineAttachType.Error)
                {
                    var newMergeLine = currentLine.NewAttachLine(curLine, attachType);
                    mFreeLines.Remove(currentLine);
                    mFreeLines.Remove(curLine);
                    mFreeLines.Add(newMergeLine);
                    return true;
                }
            }

            return false;
        }

    }
}