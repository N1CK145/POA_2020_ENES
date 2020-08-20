using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Data.SqlClient;
using System.Data;
using System.Threading;


namespace POA_2020_GUI
{
    /// <summary>
    /// Interaktionslogik für Loginscreen.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public static MainWindow mainWindw;

        public MainWindow()
        {
            InitializeComponent();
            mainWindw = this;
        }

        private void closeclick(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void BtnSubmit_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}