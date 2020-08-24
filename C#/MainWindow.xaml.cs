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
using POA_2020_GUI.utils;
using System.Threading.Tasks;

namespace POA_2020_GUI
{
    /// <summary>
    /// Interaktionslogik für Loginscreen.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        DB_Connection con;

        public MainWindow()
        {
            InitializeComponent();
            con = new DB_Connection("lia-gaming.de", "POA_2020", "schule", "123");
        }

        private void closeclick(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private async void BtnSubmit_Click(object sender, RoutedEventArgs e)
        {
            con.Open();
            DataTable dt = await con.QuerryAsync($"SELECT * FROM tbl_User WHERE Gelegenheitsunternehmensangestellteidentifikationsnummer LIKE '{txt_Username.Text}' AND Pin LIKE '{ txt_Password.Password }';");
            if (dt.Rows.Count == 1)
            {
                con.Close();
                new Menue().Show();
                this.Close();
            }
            else
            {
                MessageBox.Show("Invalid User", "Error");
                con.Close();
            }

        }
    }
}