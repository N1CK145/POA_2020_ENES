using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using POA_2020_GUI.utils;

namespace POA_2020_GUI.objects
{
    public class SecuritySystem
    {
        public static SecuritySystem Instance;

        public bool isEnabled;
        public int personsInRoomCount;
        public ActivityLogManager activityLogManager;
        public UserManager UserManager;
        public DeviceManager DeviceManager;

        public SecuritySystem()
        {
            Instance = this;
        }

        public async Task updateDataAsync(DB_Connection con)
        {
            activityLogManager = new ActivityLogManager();
            DeviceManager = new DeviceManager();
            UserManager = new UserManager();

            con.Open();

            DataTable dt_personInRoom = await con.QuerryAsync("SELECT ID, UserID, DeviceID_Login, Time_Login FROM v_personsInRoom;");
            DataTable dt_user = await con.QuerryAsync("SELECT * FROM tbl_User;");
            DataTable dt_devices = await con.QuerryAsync("SELECT * FROM tbl_Devices;");
            DataTable dt_activityLog = await con.QuerryAsync("SELECT * FROM tbl_ActivityLog WHERE DeviceID_Logout IS NOT NULL;");
            
            con.Close();

            personsInRoomCount = dt_personInRoom.Rows.Count;
            isEnabled = personsInRoomCount > 0;

            // All user
            foreach (DataRow item in dt_user.Rows)
            {
                UserManager.AddUser(new User(
                        Int32.Parse(item[0].ToString()),
                        item[1].ToString(),
                        item[2].ToString(),
                        item[3].ToString(),
                        item.Field<DateTime>(4)
                    ));
            }
            

            // User in Room
            foreach (DataRow item in dt_personInRoom.Rows)
            {
                UserManager.GetUser(Int32.Parse(item[1].ToString())).IsLoggedIn = true;
            }

            // Devices
            foreach (DataRow item in dt_devices.Rows)
            {
                DeviceManager.AddDevice(new Device(
                        Int32.Parse(item[0].ToString()),
                        item[1].ToString()
                    ));
            }
        }
    }
}
