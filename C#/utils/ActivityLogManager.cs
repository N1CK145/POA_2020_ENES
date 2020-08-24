using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using POA_2020_GUI.objects;

namespace POA_2020_GUI.utils
{
    public class ActivityLogManager
    {
        public List<ActivityLogEntry> ActivityList { get; }

        public ActivityLogManager()
        {
            ActivityList = new List<ActivityLogEntry>();
        }

        public void AddActivityLogEntry(ActivityLogEntry e)
        {
            ActivityList.Add(e);
        }

        public ActivityLogEntry GetActivityLogEntry(int id)
        {
            return ActivityList.Find(x => x.ID == id);
        }

        public void RemoveActivityLogEntry(ActivityLogEntry e)
        {
            ActivityList.Remove(e);
        }
    }
}
