// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using Medusa.Siren.Schema;

namespace UnityClient.Proto
{
  	[SirenClass]
	public class LoginResponse
	{
		[SirenField]
		public int Error { get; set; }
	}


}
