#region

using System;
using System.Runtime.InteropServices;

#endregion

namespace MonoTestLibrary
{
    public static class Program
    {
        public enum UserNotificationType
        {
            Stop = 0,
            Alert = 1,
            Caution = 2,
            Plain = 3
        }

        [DllImport("libbootstrap.dylib", CharSet = CharSet.Auto)]
        private static extern void UserNotificationDisplayNotice(string title, string message, UserNotificationType type);

        public static void EntryPoint()
        {
            Console.WriteLine("Hello Mono world!");
            UserNotificationDisplayNotice("Hello", "Hello Mono world!", UserNotificationType.Alert);
        }
    }
}
