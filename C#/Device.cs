using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POA_2020_GUI
{
    class Device
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