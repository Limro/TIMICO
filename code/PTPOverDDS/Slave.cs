using System;
using System.Collections.Generic;
using System.Text;
using DDS;
using System.Threading;
using System.Diagnostics;
using RTI.Connext.RequestReply;

namespace PTP
{

    public class Slave : IDisposable
    {
        //PTP stuff
        long Delay = 0;
        long syncTs = 0; //TS at last sync
        long syncTm = 0; //TM at last sync

        public Clock clock;

        //DDS stuff
        MsgListener reader_listener;
        Requester<Msg, Msg> requester;
        DomainParticipant participant;
        Subscriber subscriber;
        Topic topic;
        DataReader reader;

        Slave()
        {
            clock = new Clock();

            reader_listener = new MsgListener();

            reader_listener.DeadlineMissed += () => Console.WriteLine("Slave: deadline missed!");
            reader_listener.DataRecieved += handleDataReceived;
        }

        void handleDataReceived(Msg data)
        {
            //Console.WriteLine("Slave: {0} received. Value:\t{1}", data.type, data.value / 10 / 1000);                        

            switch (data.type)
            {
                case MsgType.SYNC:
                    syncTs = clock.Now.Ticks;
                    break;
                case MsgType.FOLLOWUP:
                    clock.Offset = syncTs - (long)data.value - Delay;
                    syncTm = (long)data.value;
                    break;
                case MsgType.DELAYRESPONSE:
                case MsgType.DELAYREQUEST:
                default:
                    break;
            }
        }

        public void setDelay(long delayTs, long delayTm)
        {
            Delay = ((syncTs - syncTm) + (delayTm - delayTs)) / 2;
            Console.WriteLine("Delay set to: {0}", Delay);
        }

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
                using(var slave = new Slave())
                {
                    slave.setup(domain_id: 0);
                    
                    const int receive_period = 2000; // milliseconds
                    while (keepRunning)
                    {
                        Console.WriteLine("Current time: {0}", slave.clock.Now);

                        long delayTs, delayTm;
                        slave.SendRequest(out delayTs, out delayTm);
                        slave.setDelay(delayTs, delayTm);

                        Thread.Sleep(receive_period);
                    }
                }
            }
            catch (System.Exception e)
            {
                Console.WriteLine("error in application: " + e.Message);
            }

            Console.WriteLine("Slave: terminating.");
            Console.ReadKey();
        }

        void setup(int domain_id)
        {
            participant = createParticipant(domain_id);
            subscriber = createSubscriber(participant);
            
            var type_name = MsgTypeSupport.get_type_name();
            MsgTypeSupport.register_type(participant, type_name);

            topic = createTopic(participant, type_name, "PTP");

            reader = createReader(participant, subscriber, topic, reader_listener);

            requester = new Requester<Msg, Msg>(participant, "PTP",
                                                            MsgTypeSupport.get_instance(),
                                                            MsgTypeSupport.get_instance());

        }

        void SendRequest(out long ts, out long tm)
        {
            var maxWait = new Duration_t { sec = 5, nanosec = 0 };
            tm = 0;

            // Send request
            var request = new Msg { type = MsgType.DELAYREQUEST };
            ts = clock.Now.Ticks;
            requester.SendRequest(request);

            // Create reply Sample
            var reply = requester.CreateReplySample();

            // Receive reply (wait for it and get the sample)
            var received = requester.ReceiveReply(reply, maxWait);
            if (received)
            {
                if (reply.Info.valid_data)
                {
                    Console.WriteLine("Slave: {0} reply received. Value:\t{1}", reply.Data.type, reply.Data.value / 10 / 1000);

                    if(reply.Data.type == MsgType.DELAYRESPONSE)
                    {
                        tm = (long)reply.Data.value;
                    }
                }
                else
                    Console.WriteLine("Received invalid reply");
            }
            else
                Console.WriteLine("Reply not received");
        }

        private static DataReader createReader(DomainParticipant participant, Subscriber subscriber, Topic topic, MsgListener reader_listener)
        {
            var reader = subscriber.create_datareader(
                topic,
                Subscriber.DATAREADER_QOS_DEFAULT,
                reader_listener,
                StatusMask.STATUS_MASK_ALL);

            if (reader == null)
                throw new ApplicationException("create_datareader error");

            return reader;
        }

        private static Topic createTopic(DomainParticipant participant, string type_name, string topicName)
        {
            var topic = participant.create_topic(
                topicName,
                type_name,
                DomainParticipant.TOPIC_QOS_DEFAULT,
                null /* listener */,
                StatusMask.STATUS_MASK_NONE);

            if (topic == null)
                throw new ApplicationException("create_topic error");

            return topic;
        }

        private static Subscriber createSubscriber(DomainParticipant participant)
        {
            var subscriber = participant.create_subscriber(
                DomainParticipant.SUBSCRIBER_QOS_DEFAULT,
                null /* listener */,
                StatusMask.STATUS_MASK_NONE);

            if (subscriber == null)
                throw new ApplicationException("create_subscriber error");

            return subscriber;
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

        static void shutdown(DomainParticipant participant)
        {
            /* Delete all entities */

            if (participant != null)
            {
                participant.delete_contained_entities();
                DomainParticipantFactory.get_instance().delete_participant(ref participant);
            }

            try
            {
                DomainParticipantFactory.finalize_instance();
            }
            catch (DDS.Exception e)
            {
                Console.WriteLine("finalize_instance error {0}", e);
                throw e;
            }
        }

        public void Dispose()
        {
            if(requester != null)
            {
                requester.Dispose();
                requester = null;
            }

            reader_listener = null;
            shutdown(participant);
        }
    }

} /* namespace PTP */
