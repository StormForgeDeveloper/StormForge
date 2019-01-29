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
        public StressTestWindowRank mRankTestWin = new StressTestWindowRank();

        public StressTestWindowMatchTest mMatcingTestWin = new StressTestWindowMatchTest();

        public StressTestWindowMatch10KB  mMatched10KBTestWin = new StressTestWindowMatch10KB();
 


        public void InitStressTest()
        {
            MainWindow.InitIPAdressComboBox(MainWindow.Instance.stress_comboBoxIPAddress, ServerAddressRegistry.GetServerAddresses(1));

            InputMethod.SetIsInputMethodEnabled(MainWindow.Instance.UserBeginIdNum, false);

            MainWindow.Instance.PreFixUserID.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_PREFIX_KEY_ID, "Braves");
            MainWindow.Instance.UserBeginIdNum.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_USER_BEGIN_NUM_KEY_ID, "3000");

            MainWindow.Instance.MatchInGroupUserCount.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_MATCHGRUCOUNT_KEY_ID, "50");
            MainWindow.Instance.MatchKBMaxUserNumber.Text = ServerAddressRegistry.ReadValue(MainWindow.SAVE_MATCHMAXUSERCOUNT_ID, "100");

          

            mMatcingTestWin.InitStressTest();
            mMatched10KBTestWin.InitStressTest();


            mRankTestWin.InitStressTest();
        }

        public void OnClosed()
        {          
            mMatcingTestWin.OnClosed();
            mMatched10KBTestWin.OnClosed();

            mRankTestWin.OnClosed();

            mMatcingTestWin = null;
            mMatched10KBTestWin = null;

            mRankTestWin = null;
        }

        public void StartMatchingTest(bool bAutoClick, int ClickIndex)
        {
            mMatcingTestWin.StartTest(bAutoClick, ClickIndex);
        }

        public void StartMatchedChatTest(bool bAutoClick, int ClickIndex)
        {
            mMatched10KBTestWin.StartTest(bAutoClick, ClickIndex);
        }

        public void StartRankTest()
        {
            mRankTestWin.StartTest();
        }

        public void SaveRankData()
        {
            mRankTestWin.ReqSaveRankData("RankData");
        }
    }
}
