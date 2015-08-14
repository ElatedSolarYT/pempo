using System;

namespace Pempo
{
	[AttributeUsage(AttributeTargets.Assembly)]
	public class EntryPointAttribute : Attribute
	{
		public string EntryPointMethod { get; private set;}

		public EntryPointAttribute(string entryPointMethod)
		{
			EntryPointMethod = entryPointMethod;
		}
	}
}

