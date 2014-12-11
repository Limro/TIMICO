using RTI.Connext.Infrastructure;
using RTI.Connext.RequestReply;
using System;

namespace PTP
{
    public class MsgReplierListener : SimpleReplierListener<Msg, Msg>
    {
        Msg reply = new Msg { type = MsgType.DELAYRESPONSE };

        public Msg OnRequestAvailable(Sample<Msg> request)
        {
            Console.WriteLine("Master: request received.");

            if (request.Info.valid_data)
            {
                reply.type = MsgType.DELAYRESPONSE;
                reply.value = (ulong)Master.getCurrentTime().Ticks;
                return reply;
            }
            else
            {
                return null;
            }
        }

        public void ReturnLoan(Msg reply)
        {
        }
    }
}
