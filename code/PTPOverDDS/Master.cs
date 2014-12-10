using System;
using System.Collections.Generic;
using System.Text;
using DDS;
using RTI.Connext.RequestReply;
using System.Threading;
using System.Diagnostics;
using RTI.Connext.Infrastructure;

namespace PTP
{

    public class Master : IDisposable
    {
        DomainParticipant participant;
        SimpleReplier<Msg, Msg> replier;
        Publisher publisher;
        Topic topic;
        MsgDataWriter writer;

        Msg instance;
        InstanceHandle_t instance_handle = InstanceHandle_t.HANDLE_NIL;

        static Random rand = new Random();

        public static void Main(string[] args)
        {
            var keepRunning = true;
            ConsoleHandler.SetConsoleEventHandler((ctrl) =>
            {
                Console.WriteLine("Termination requested.");
                keepRunning = false;
                return true;
            });

            try
            {
                using (var master = new Master())
                {
                    master.setup(domain_id: 0);

                    const int send_period = 485; // milliseconds
                    
                    while (keepRunning)
                    {
                        var tm = getCurrentTime();

                        //Console.WriteLine("Master: sending {0}", instance.value / 10 / 1000);

                        master.sendSync(tm + jitter());
                        master.sendFollowup(tm);                        

                        Thread.Sleep(send_period);
                    }
                }
            }
            catch (System.Exception e)
            {
                Console.WriteLine("error in master: " + e.Message);
            }

            Console.WriteLine("Master: terminating.");
            Console.ReadKey();
        }

        public void sendSync(long estimatedTm)
        {
            instance.type = MsgType.SYNC;
            instance.value = (ulong)estimatedTm;
            writer.write(instance, ref instance_handle);
        }

        public void sendFollowup(long tm)
        {
            instance.type = MsgType.FOLLOWUP;
            instance.value = (ulong)tm;
            writer.write(instance, ref instance_handle);
        }

        public static long getCurrentTime()
        {
            return DateTime.Now.Ticks;
        }

        public static long jitter()
        {
            var isPositive = rand.Next(1, 2) > 1;

            long jitter = rand.Next(1000);

            return isPositive ? jitter : -jitter;
        }

        public void setup(int domain_id)
        {
            participant = createParticipant(domain_id);

            replier = new SimpleReplier<Msg, Msg>(participant, "PTP", new MsgReplierListener(),
                                                        MsgTypeSupport.get_instance(), MsgTypeSupport.get_instance());

            var publisher = createPublisher(participant);

            /* Register type before creating topic */
            var type_name = MsgTypeSupport.get_type_name();
            MsgTypeSupport.register_type(participant, type_name);

            topic = createTopic(participant, type_name, "PTP");

            writer = createWriter(publisher, topic);

            instance = MsgTypeSupport.create_data();
            if (instance == null)
                throw new ApplicationException("MsgTypeSupport.create_data error");
        }

        private static MsgDataWriter createWriter(Publisher publisher, Topic topic)
        {
            var Msg_writer = (MsgDataWriter)publisher.create_datawriter(topic, Publisher.DATAWRITER_QOS_DEFAULT, null /* listener */,
                                        StatusMask.STATUS_MASK_NONE);

            if (Msg_writer == null)
                throw new ApplicationException("create_datawriter error");

            return Msg_writer;
        }

        private static Topic createTopic(DomainParticipant participant, string type_name, string topicName)
        {
            var topic = participant.create_topic(topicName, type_name, DomainParticipant.TOPIC_QOS_DEFAULT, null /* listener */,
                                                    StatusMask.STATUS_MASK_NONE);

            if (topic == null)
                throw new ApplicationException("create_topic error");

            return topic;
        }

        private static Publisher createPublisher(DomainParticipant participant)
        {
            var publisher = participant.create_publisher(DomainParticipant.PUBLISHER_QOS_DEFAULT, null /* listener */,
                                                         StatusMask.STATUS_MASK_NONE);
            if (publisher == null)
                throw new ApplicationException("create_publisher error");

            return publisher;
        }

        private static DomainParticipant createParticipant(int domain_id)
        {
            var participant = DomainParticipantFactory.get_instance().create_participant(
                    domain_id,
                    DomainParticipantFactory.PARTICIPANT_QOS_DEFAULT,
                    null /* listener */,
                    StatusMask.STATUS_MASK_NONE);

            if (participant == null)
                throw new ApplicationException("create_participant error");

            return participant;
        }

        public void Dispose()
        {
            try
            {
                if(replier != null)
                {
                    replier.Dispose();
                    replier = null;
                }
                
                if (participant != null)
                {
                    participant.delete_contained_entities();
                    DomainParticipantFactory.get_instance().delete_participant(ref participant);
                }

                if (instance != null)
                    MsgTypeSupport.delete_data(instance);

                DomainParticipantFactory.finalize_instance();
            }
            catch (DDS.Exception e)
            {
                Console.WriteLine("finalize_instance error: {0}", e);
                throw e;
            }
        }
    }

}
