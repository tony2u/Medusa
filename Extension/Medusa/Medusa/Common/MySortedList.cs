// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System;
using System.Collections;
using System.Collections.Generic;

namespace Medusa.Common
{
    public class MySortedList<T> : IList<T> where T : IComparable<T>
    {
        private readonly List<T> mList = new List<T>();

        public T First
        {
            get { return mList[0]; }
        }

        public IEnumerator<T> GetEnumerator()
        {
            return mList.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return mList.GetEnumerator();
        }

        public void Add(T item)
        {
            mList.Add(item);
            mList.Sort();
        }

        public void Clear()
        {
            mList.Clear();
        }

        public bool Contains(T item)
        {
            return mList.Contains(item);
        }

        public void CopyTo(T[] array, int arrayIndex)
        {
            mList.CopyTo(array, arrayIndex);
        }

        public bool Remove(T item)
        {
            return mList.Remove(item);
        }

        public int Count
        {
            get { return mList.Count; }
        }

        public bool IsReadOnly
        {
            get { return false; }
        }

        public int IndexOf(T item)
        {
            return mList.IndexOf(item);
        }

        public void Insert(int index, T item)
        {
            mList.Insert(index, item);
        }

        public void RemoveAt(int index)
        {
            mList.RemoveAt(index);
        }


        public T this[int index]
        {
            get { return mList[index]; }
            set { mList[index] = value; }
        }

        public void AddRange(IEnumerable<T> collection)
        {
            mList.AddRange(collection);
        }

        public void RemoveRange(IEnumerable<T> collection)
        {
            foreach (var item in collection)
            {
                mList.Remove(item);
            }
        }

        public override string ToString()
        {
            return Count.ToString();
        }
    }
}