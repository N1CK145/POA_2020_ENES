using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using MySql.Data.MySqlClient;

namespace Login.utils
{
    class DB_Connection
    {
        private string conString;
        private MySqlConnection mySqlConnection;
        private MySqlDataAdapter mySqlDataAdapter;

        public DB_Connection(string user, string pwd, string host, string db)
        {
            conString = $"SERVER={host}; DATABASE={db}; UID={user}; PASSWORD{pwd}; DATABASE={db};";
            initVars();
        }

        public DB_Connection(string user, string pwd, string host, string db, string port)
        {
            conString = $"SERVER={host}; DATABASE={db}; UID={user}; PASSWORD{pwd}; DATABASE={db}; PORT={port}";
            initVars();
        }

        private void initVars()
        {
            mySqlConnection = new MySqlConnection();
            mySqlDataAdapter = new MySqlDataAdapter();
            mySqlConnection.ConnectionString = conString;
        }

        public void Open()
        {
            try
            {
                mySqlConnection.Open();
            }
            catch(Exception e)
            {
                MessageBox.Show(e.ToString());
            }
        }

        public void Close()
        {
            try
            {
                mySqlConnection.Close();
                mySqlConnection.Dispose();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
        }
    }
}
