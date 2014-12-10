using DDS;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PTP
{
    public class MsgListener : DataReaderListener
    {
        MsgSeq data_seq;
        SampleInfoSeq info_seq;

        public event Action DeadlineMissed;
        public event Action<Msg> DataRecieved;

        public MsgListener()
        {
            data_seq = new MsgSeq();
            info_seq = new SampleInfoSeq();
        }

        public override void on_requested_deadline_missed(DataReader reader, ref RequestedDeadlineMissedStatus status)
        {
            var handler = DeadlineMissed;
            if (handler != null)
                handler();
        }

        public override void on_data_available(DataReader reader)
        {
            var Msg_reader = (MsgDataReader)reader;

            try
            {
                Msg_reader.take(data_seq, info_seq,
                    ResourceLimitsQosPolicy.LENGTH_UNLIMITED,
                    SampleStateKind.ANY_SAMPLE_STATE,
                    ViewStateKind.ANY_VIEW_STATE,
                    InstanceStateKind.ANY_INSTANCE_STATE);
            }
            catch (Retcode_NoData)
            {
                return;
            }
            catch (DDS.Exception e)
            {
                Console.WriteLine("take error {0}", e);
                return;
            }

            var data_length = data_seq.length;
            for (int i = 0; i < data_length; ++i)
            {
                if (info_seq.get_at(i).valid_data)
                {
                    var data = data_seq.get_at(i);

                    var handler = DataRecieved;
                    if (handler != null)
                        handler(data);
                }
            }

            try
            {
                Msg_reader.return_loan(data_seq, info_seq);
            }
            catch (DDS.Exception e)
            {
                Console.WriteLine("return loan error {0}", e);
            }
        }

    };
}
