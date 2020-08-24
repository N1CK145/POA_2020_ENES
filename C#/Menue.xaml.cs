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
using System.Windows.Shapes;

using System.Threading;
using System.Windows.Threading;
using POA_2020_GUI.utils;
using System.Data;
using POA_2020_GUI.objects;

namespace POA_2020_GUI
{
    /// <summary>
    /// Interaktionslogik für Menue.xaml
    /// </summary>
    public partial class Menue : Window
    {
        public static DB_Connection con;
        public SecuritySystem securitySystem;

        public Menue()
        {
            securitySystem = new SecuritySystem();
            con = new DB_Connection("lia-gaming.de", "POA_2020", "schule", "123");

            InitializeComponent();
            updateClock();

            updateInformation();
        }

        private void updateInformation()
        {
            Task.WaitAll(Task.Run(() => securitySystem.updateDataAsync(con)));

            if (securitySystem.isEnabled)
            {
                Canvas_SecuritySystemStatus.Background = Brushes.DarkGreen;
                Icon_SecuritySystemStatus.Kind = MaterialDesignThemes.Wpf.PackIconKind.Done;
                Label_SecuritySystemStatus.Content = "Enabled";
            }
            else
            {
                Canvas_SecuritySystemStatus.Background = Brushes.DarkRed;
                Icon_SecuritySystemStatus.Kind = MaterialDesignThemes.Wpf.PackIconKind.ErrorOutline;
                Label_SecuritySystemStatus.Content = "Disabled";
            }

            Label_DashBoard_PersonInRoomCount.Content = "Person count in room:" + securitySystem.personsInRoomCount;

            Label_DashBoard_PersonInRoomCount.ToolTip = "";
            foreach (User user in securitySystem.UserManager.UserList.FindAll(x => x.IsLoggedIn == true))
            {
                Label_DashBoard_PersonInRoomCount.ToolTip += $"{user.Nachname}, {user.Vorname}\n";
            }

            
            Label_DashBoard_SecurtySystemStatus.Content = "Securitysystem Status: " + securitySystem.isEnabled;
        }

        private void CloseWindowButtonClick(object sender, RoutedEventArgs e)
        {
            Close();
        }
        
        private void updateClock()
        {
            Label_DashBoard_Clock.Content = DateTime.Now.ToString("HH:mm") + " Uhr";

            DispatcherTimer timer = new DispatcherTimer(new TimeSpan(0, 0, 1), DispatcherPriority.Normal, delegate
            {
                if (Label_DashBoard_Clock.Content.ToString().Contains(":"))
                    Label_DashBoard_Clock.Content = DateTime.Now.ToString("HH mm") + " Uhr";
                else
                    Label_DashBoard_Clock.Content = DateTime.Now.ToString("HH:mm") + " Uhr";
            }, Dispatcher);
        }
    }
}
