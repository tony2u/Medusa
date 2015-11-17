// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.IO;
using System.Linq;
using GameKit.Common;
using GameKit.Log;
using GameKit.Publish;
using GameKit.Resource;

namespace GameKit.Packing
{
    public class ImageMerger
    {
        public Dictionary<ImageFile, ImageLayouter> Generate(PublishGroup publishGroup, MySortedList<ImageFile> inputFiles)
        {
            bool isPOT = inputFiles.All(inputFile => inputFile.IsPOT);
            bool isSquare = inputFiles.All(inputFile => inputFile.IsSquare);


            var imageLayouts = LayoutImage(publishGroup, inputFiles, isPOT, isSquare);
            foreach (var imageLayouter in imageLayouts)
            {
                MergeImages(imageLayouter.Key, imageLayouter.Value);
            }

            return imageLayouts;
        }

        private Dictionary<ImageFile, ImageLayouter> LayoutImage(PublishGroup publishGroup, MySortedList<ImageFile> bitmaps,bool isPOT,bool isSquare)
        {
            var result = new Dictionary<ImageFile, ImageLayouter>();
            uint order = 0;
            while (bitmaps.Count > 0)
            {
                var layouter = new ImageLayouter(PublishTarget.Current.DefaultImageSize, PublishTarget.Current.MaxImageSize, isPOT, isSquare);
                var copyList = new MySortedList<ImageFile>();
                copyList.AddRange(bitmaps);

                layouter.Generate(copyList);
                bitmaps.RemoveRange(layouter.UsedImages);

                if (layouter.ResultImageFixedSize != Size.Empty)
                {
                    FileInfo newFile = new FileInfo(publishGroup.GenerateNewFileName(PathManager.OutputImagesPath, order));
                    var resultImage = new ImageFile(newFile,true,true)
                        {
                            TextureRect = new Rectangle(Point.Empty, layouter.ResultImageFixedSize)
                        };

                    resultImage.Order = order;
                    if (PublishTarget.Current.IsPVR)
                    {
                        resultImage.IsPVREnabled = layouter.UsedImages.All(usedImage => usedImage.IsPVREnabled);
                    }
                    else
                    {
                        resultImage.IsPVREnabled = false;
                    }
                    
                    result.Add(resultImage, layouter);
                    Logger.LogInfo("\t\tPack Image:{0}:\r\n", resultImage.FileInfo.Name);

                }
                else
                {
                    foreach (var usedImage in layouter.UsedImages)
                    {
                        Logger.LogInfo("\t\tToo Big Image:{0}:\r\n", usedImage);
                    }
                }
                ++order;
            }



            //foreach (var mergeResult in result)
            //{
            //    Logger.LogInfo("\t{0} {1}=>{2}:\r\n", mergeResult.Key, mergeResult.Value.ResultImageSize,
            //                   mergeResult.Value.ResultImageFixedSize);

            //    foreach (var imageFile in mergeResult.Value.UsedImages)
            //    {
            //        Logger.LogInfo("\t\t{0}:\r\n", imageFile);
            //    }
            //}

            return result;
        }

        private void MergeImages(ImageFile resultImage, ImageLayouter imageFiles)
        {
            if (resultImage.ResultImage == null)
            {
                if (resultImage.TextureRect != null)
                {
                    resultImage.ResultImage = new Bitmap(resultImage.TextureRect.Value.Size.Width,
                        resultImage.TextureRect.Value.Size.Height);
                    resultImage.ResultSize = resultImage.ResultImage.Size;
                }

            }

            if (resultImage.ResultImage != null)
                using (var graphics = Graphics.FromImage(resultImage.ResultImage))
                {
                    graphics.Clear(Color.Transparent);
                    graphics.CompositingQuality = CompositingQuality.HighQuality;
                    graphics.SmoothingMode = SmoothingMode.HighQuality;
                    graphics.InterpolationMode = InterpolationMode.HighQualityBicubic;

                    foreach (var bitmap in imageFiles.UsedImages)
                    {
                        bitmap.IsPacked = true;
                        if (bitmap.TextureRect != null)
                        {
                            if (bitmap.ResultImage == null)
                            {
                                bitmap.ResultImage = (Bitmap)Bitmap.FromFile(bitmap.FileInfo.FullName);
                            }
                            graphics.DrawImage(bitmap.ResultImage, bitmap.TextureRect.Value);
                            bitmap.ResultImage.Dispose();
                            bitmap.ResultImage = null;
                        }


                    }
                }


            //resultImage.Save();


            //uint fileId = FileSystemGenerator.AddFile(resultImage.ResultFile);
            //if (fileId != uint.MaxValue)
            //{
            //    foreach (var imageFile in imageFiles.UsedImages)
            //    {
            //        imageFile.ResultFile = resultImage.ResultFile;
            //        FileSystemGenerator.AddTagItem(imageFile, fileId);
            //    }
            //}

        }
    }
}