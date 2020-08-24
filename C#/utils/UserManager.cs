using POA_2020_GUI.objects;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace POA_2020_GUI.utils
{
    public class UserManager
    {
        public List<User> UserList { get; }

        public UserManager()
        {
            UserList = new List<User>();
        }

        public void AddUser(User u)
        {
            UserList.Add(u);
        }

        public void RemoveUser(User u)
        {
            UserList.Remove(u);
        }

        public User GetUser(int id)
        {
            return UserList.Find(user => user.ID == id);
        }
    }
}
