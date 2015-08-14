using System;
using System.Runtime.InteropServices;

namespace Pempo
{
	public static class Program
	{
		public enum UserNotificationLevel: int 
		{
			Stop = 0,
			Alert = 1,
			Caution = 2,
			Plain = 3
		}

		[DllImport("libbootstrap.dylib", CharSet=CharSet.Auto)]
		private static extern void UserNotificationDisplayNotice(string title, string message, UserNotificationLevel type);

		public static void EntryPoint()
		{
			Console.WriteLine("Hello Mono world!");
			UserNotificationDisplayNotice("Hello", "Hello Mono world!", UserNotificationLevel.Stop);
		}
	}
}

