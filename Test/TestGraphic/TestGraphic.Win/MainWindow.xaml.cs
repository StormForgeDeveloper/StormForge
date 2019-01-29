using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using SF;
using System.Windows.Interop;

namespace TestGraphic.Win
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Engine m_Engine;
        RenderWindow m_RenderWindow;


        public MainWindow()
        {
            InitializeComponent();

            m_Engine = new Engine();
            m_Engine.StartEngineWithGraphic();
        }

        private void OnMainWindowLoaded(object sender, RoutedEventArgs e)
        {
            m_RenderWindow = new RenderWindow(RenderWindowParent.ActualWidth, RenderWindowParent.ActualHeight);
            RenderWindowParent.Child = m_RenderWindow;

            m_Engine.OnWindowCreated(m_RenderWindow.Handle);
        }


        protected override void OnClosed(EventArgs e)
        {
            if (m_Engine != null)
                m_Engine.StopEngine();
            m_Engine = null;

            base.OnClosed(e);
        }



        private void OnGameViewSizeChanged(object sender, SizeChangedEventArgs e)
        {
            if(m_RenderWindow != null)
                m_Engine.OnWindowResized();
        }


        private void OnGameViewUnloaded(object sender, RoutedEventArgs e)
        {
            m_Engine.OnWindowClosed(m_RenderWindow.Handle);
        }

    }
}
