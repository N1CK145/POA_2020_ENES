using POA_2020_GUI.objects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POA_2020_GUI.utils
{
    public class DeviceManager
    {
        public List<Device> DeviceList;

        public DeviceManager()
        {
            DeviceList = new List<Device>();
        }

        public void AddDevice(Device d)
        {
            DeviceList.Add(d);
        }

        public Device GetDevice(int id)
        {
            return DeviceList.Find(device => device.ID == id);
        }

        public void RemoveDevice(Device d)
        {
            DeviceList.Remove(d);
        }
    }
}
