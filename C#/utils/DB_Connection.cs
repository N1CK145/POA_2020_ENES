using System;
using System.Collections.Generic;
using MySql.Data.MySqlClient;
using System.Data;
using System.Threading.Tasks;

namespace POA_2020_GUI.utils
{
    /// <summary>
    /// Die Klasse <c>DB_Connection</c> ist eine Klasse, die
    /// Basismethoden bereitstellt um den Umgang mit einer MySQL Datenbank zu erleichtern.
    /// </summary>
    public class DB_Connection
    {
        private string connectionString;
        public MySqlConnection Connection;

        public DB_Connection(string server, string db, string user, string pwd)
        {
            connectionString = $"SERVER={server};DATABASE={db};UID={user};PWD={pwd};";
            Connection = new MySqlConnection();
        }

        /// <summary>
        /// Eröffnet eine neue Verbindung zu einer MySQL Datenbank. Die
        /// Verbindungsinformationen werden aus dem <c>connectionString</c> ausgelesen.
        /// Dieser wird im <c>Konstruktor</c> mit den nötigen Informationen gefüllt.
        /// </summary>
        public void Open()
        {
            Connection.ConnectionString = connectionString;
            Connection.Open();
        }
        /// <summary>
        /// Schließt die Verbindung zum MySQL-Server, falls vorhanden.
        /// </summary>
        public void Close()
        {
            Connection.Close();
        }
        /// <summary>
        /// Sendet eine Querry an den MySQL-Server. Als Rückgabe wird die Tabelle geliefert.
        /// </summary>
        public DataTable Querry(string querry)
        {
            DataTable dt = new DataTable();
            MySqlDataAdapter da = new MySqlDataAdapter();

            da.SelectCommand = new MySqlCommand(querry, Connection);
            da.Fill(dt);

            return dt;
        }

        public async Task<DataTable> QuerryAsync(string querry)
        {
            return await Task.Run(() => Querry(querry));
        }

        /// <summary>
        /// Gibt den Integer der Ersten spalte der ersten Zeile des Querry Ergebnisses zurück.
        /// </summary>
        public int GetInt(string querry)
        {
            return Int32.Parse(Querry(querry).Rows[0].ItemArray[0].ToString());
        }
        /// <summary>
        /// Gibt den String/Varchar der Ersten spalte der ersten Zeile des Querry Ergebnisses zurück.
        /// </summary>
        public string GetString(string querry)
        {
            DataTable dt = Querry(querry);
            return dt.Rows[0].ItemArray[0].ToString();
        }
        /// <summary>
        /// Gibt den Zeitstempel der Ersten spalte der ersten Zeile des Querry Ergebnisses zurück.
        /// </summary>
        public DateTime GetDateTime(string querry)
        {
            return DateTime.Parse(GetString(querry));
        }
        /// <summary>
        /// Überprüft, ob ein MySQL-User existiert. Das Ergebniss wird als Boolean geliefert.
        /// </summary>
        public bool UserExist(string user)
        {
            if (Querry($"SELECT Host, User FROM mysql.user WHERE User LIKE '{user}';").Rows.Count != 0)
                return true;

            return false;
        }
        /// <summary>
        /// Erstellt einen Neuen MySQL-User.
        /// </summary>
        public void CreateUser(string user, string password)
        {
            Querry($"CREATE USER '{user}' IDENTIFIED BY '{password}';");

        }
        /// <summary>
        /// Gibt eine Spalte als String Liste zurück.
        /// </summary>
        public List<string> GetColumn(string querry, int index)
        {
            List<string> l = new List<string>();
            MySqlDataReader reader = new MySqlCommand(querry, Connection).ExecuteReader();

            while (reader.Read())
            {
                l.Add(reader[index].ToString());
            }
            reader.Close();
            return l;
        }
    }
}
