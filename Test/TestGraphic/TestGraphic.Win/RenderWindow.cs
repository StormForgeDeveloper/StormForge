using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace TestGraphic.Win
{
    class RenderWindow : HwndHost
    {
        internal const int
              WS_CHILD = 0x40000000,
              WS_VISIBLE = 0x10000000,
              LBS_NOTIFY = 0x00000001,
              HOST_ID = 0x00000002,
              LISTBOX_ID = 0x00000001,
              WS_VSCROLL = 0x00200000,
              WS_BORDER = 0x00800000;


        IntPtr hwndHost;
        int m_Height, m_Width;

        public RenderWindow(double height, double width)
        {
            m_Height = (int)height;
            m_Width = (int)width;
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            //hwndControl = IntPtr.Zero;
            hwndHost = IntPtr.Zero;

            hwndHost = CreateWindowEx(0, "static", "",
                                      WS_CHILD | WS_VISIBLE,
                                      0, 0,
                                      m_Width, m_Height,
                                      hwndParent.Handle,
                                      (IntPtr)HOST_ID,
                                      IntPtr.Zero,
                                      0);


            return new HandleRef(this, hwndHost);
        }

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            handled = false;
            return IntPtr.Zero;
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            DestroyWindow(hwnd.Handle);
        }


        //PInvoke declarations
        [DllImport("user32.dll", EntryPoint = "CreateWindowEx", CharSet = CharSet.Unicode)]
        internal static extern IntPtr CreateWindowEx(int dwExStyle,
                                                      string lpszClassName,
                                                      string lpszWindowName,
                                                      int style,
                                                      int x, int y,
                                                      int width, int height,
                                                      IntPtr hwndParent,
                                                      IntPtr hMenu,
                                                      IntPtr hInst,
                                                      [MarshalAs(UnmanagedType.AsAny)] object pvParam);

        [DllImport("user32.dll", EntryPoint = "DestroyWindow", CharSet = CharSet.Unicode)]
        internal static extern bool DestroyWindow(IntPtr hwnd);
    }
}
