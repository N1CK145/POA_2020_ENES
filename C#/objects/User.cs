using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POA_2020_GUI.objects
{
    public class User
    {
        private int id;

        public int ID
        {
            get { return id; }
            set { id = value; }
        }

        private string vorname;

        public string Vorname
        {
            get { return vorname; }
            set { vorname = value; }
        }

        private string nachname;

        public string Nachname
        {
            get { return nachname; }
            set { nachname = value; }
        }

        private string pin;

        public string Pin
        {
            get { return pin; }
            set { pin = value; }
        }

        private DateTime createdat;

        public DateTime Createdat
        {
            get { return createdat; }
            set { createdat = value; }
        }

        private bool isLoggedIn;

        public bool IsLoggedIn
        {
            get { return isLoggedIn; }
            set { isLoggedIn = value; }
        }


        public User(int id, string vorname, string nachname, string pin, DateTime createdat)
        {
            this.id = id;
            this.vorname = vorname;
            this.nachname = nachname;
            this.pin = pin;
            this.createdat = createdat;
            isLoggedIn = false;
        }
    }
}