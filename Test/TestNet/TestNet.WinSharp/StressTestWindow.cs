using System;
using System.Windows;
using System.Windows.Controls;
using System.Collections.Generic;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;


using SF;
using Microsoft.Win32;
using System.Threading;
using System.IO;

namespace TestNet.WinSharp
{
    public class StressTestWindow
    {
        public StressTestWindowDataTest mDataTestWin = new StressTestWindowDataTest();
        public StressTestWindowMatchTest mMatcingTestWin = new StressTestWindowMatchTest();

        public StressTestWindowMatch10KB  mMatched10KBTestWin = new StressTestWindowMatch10KB();

        public StressTestWindowLoginTest mLoginTestWin = new StressTestWindowLoginTest();

        public void InitStressTest()
        {
            MainWindow.InitIPAdressComboBox(MainWindow.Instance.stress_comboBoxIPAddress, ServerAddressRegistry.GetServerAddresses(1));

            InputMethod.SetIsInputMethodEnabled(MainWindow.Instance.UserBeginIdNum, false);


            MainWindow.Instance.PreFixUserID.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_PREFIX_KEY_ID, "Braves");
            MainWindow.Instance.UserBeginIdNum.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_USER_BEGIN_NUM_KEY_ID, "3000");

            MainWindow.Instance.TenKBInGroupUserCount.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_TENKBGRUCOUNT_KEY_ID, "50");
            MainWindow.Instance.TenKBMaxUserNumber.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_TENKBMAXUSERCOUNT_KEY_ID, "100");

            MainWindow.Instance.MatchInGroupUserCount.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_MATCHGRUCOUNT_KEY_ID, "50");
            MainWindow.Instance.MatchKBMaxUserNumber.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_MATCHMAXUSERCOUNT_ID, "100");

            MainWindow.Instance.TestLoginInGroupUserCount.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_LOGINTGRUCOUNT_KEY_ID, "50");
            MainWindow.Instance.TestLoginMaxUserNumber.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_LOGINTMAXUSERCOUNT_ID, "100");


            mDataTestWin.InitStressTest();
            mMatcingTestWin.InitStressTest();
            mMatched10KBTestWin.InitStressTest();
            mLoginTestWin.InitStressTest();
        }

        public void OnClosed()
        {
            mDataTestWin.OnClosed();
            mMatcingTestWin.OnClosed();
            mMatched10KBTestWin.OnClosed();
            mLoginTestWin.OnClosed();

            mDataTestWin = null;
            mMatcingTestWin = null;
            mMatched10KBTestWin = null;
            mLoginTestWin = null;
        }

        public void StartDataTest(bool bAutoClick, int ClickIndex)
        {
            mDataTestWin.StartTest(bAutoClick, ClickIndex);
        }

        public void StartMatchingTest(bool bAutoClick, int ClickIndex)
        {
            mMatcingTestWin.StartTest(bAutoClick, ClickIndex);
        }

        public void StartMatchedChatTest(bool bAutoClick, int ClickIndex)
        {
            mMatched10KBTestWin.StartTest(bAutoClick, ClickIndex);
        }

        public void StartLoginTest(bool bAutoClick, int ClickIndex)
        {
            mLoginTestWin.StartTest(bAutoClick, ClickIndex);
        }

    }
}
