using System;

namespace Pempo
{
	[AttributeUsage(AttributeTargets.Assembly)]
	public class AssemblyEntryPointAttribute : Attribute
	{
		public string EntryPointMethod { get; private set;}

		public AssemblyEntryPointAttribute(string entryPointMethod)
		{
			EntryPointMethod = entryPointMethod;
		}
	}
}

