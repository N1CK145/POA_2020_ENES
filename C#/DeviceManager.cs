using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POA_2020_GUI
{
    class DeviceManager
    {
        public List<Device> DeviceList { get; }

        public DeviceManager()
        {
            DeviceList = new List<Device>();
        }

        public void GetDataToDatabase()
        {
            
        }
        
        public void SetDataToDatabase()
        {

        }

        public void CreateDevice(Device device)
        {
            DeviceList.Add(device);
        } 
        
        public void DeleteDevice()
        {

        }

        public void UpdateDevice()
        {

        }

        public void ReadDevice()
        {

        }
    }
}
