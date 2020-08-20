using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POA_2020_GUI
{
    class ActivityLogEntry
    {
        private int id;

        public int ID
        {
            get { return id; }
            set { id = value; }
        }

        private int userID;

        public int UserID
        {
            get { return userID; }
            set { userID = value; }
        }

        private int deviceID_Login;

        public int DeviceID_Login
        {
            get { return deviceID_Login; }
            set { deviceID_Login = value; }
        }

        private int deviceID_Logout;

        public int DeviceID_Logout
        {
            get { return deviceID_Logout; }
            set { deviceID_Logout = value; }
        }

        private DateTime time_Login;

        public DateTime Time_Login
        {
            get { return time_Login; }
            set { time_Login = value; }
        }

        private DateTime time_Logout;

        public DateTime Time_Logout
        {
            get { return time_Logout; }
            set { time_Logout = value; }
        }

        public ActivityLogEntry(int id, int userID, int deviceID_Login, int deviceID_Logout, DateTime time_Login, DateTime time_Logout)
        {
            this.id = id;
            this.userID = userID;
            this.deviceID_Login = deviceID_Login;
            this.deviceID_Logout = deviceID_Logout;
            this.time_Login = time_Login;
            this.time_Logout = time_Logout;
        }
    }
}
