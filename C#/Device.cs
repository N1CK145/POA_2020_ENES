using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POA_2020_GUI.objects
{
<<<<<<< HEAD:C#/objects/Device.cs
    public class Device
=======
    class Device
>>>>>>> 2d55aaf0a8b7ed4af74eec1b11d7b6770b1f94f0:C#/Device.cs
    {
        private int id;

        public int ID
        {
            get { return id; }
            set { id = value; }
        }

        private string bezeichnung;

        public string Bezeichnung
        {
            get { return bezeichnung; }
            set { bezeichnung = value; }
        }

        public Device(int id, string bezeichnung)
        {
            this.id = id;
            this.bezeichnung = bezeichnung;
        }
    }
}