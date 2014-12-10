using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PTP
{
    public class Clock
    {
        long lastElapsed = 0;
        long now;
        long offset;
        Stopwatch sw;

        public Clock()
        {
            now = DateTime.Now.Ticks;
            sw = Stopwatch.StartNew();
        }

        public long Offset 
        {
            set 
            {
                Console.WriteLine("Clock: time adjusted by offset: " + offset);
                now -= value;
                offset = value;
            }
            get 
            {
                return offset;
            }
        }

        public DateTime Now
        {
            get { return new DateTime(GetTime(), DateTimeKind.Local);}
        }

        long GetTime()
        {
            var elapsed = sw.Elapsed.Ticks;
            now += elapsed - lastElapsed;

            lastElapsed = elapsed;

            return now;
        }
    }
}
