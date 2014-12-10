using System;
using System.Collections.Generic;
using System.Text;
using DDS;
using RTI.Connext.RequestReply;
using System.Threading;
using System.Diagnostics;
using RTI.Connext.Infrastructure;

namespace PTP{

public class MsgPublisher {

    class MsgReplierListener : SimpleReplierListener<Msg, Msg>
    {
        Msg reply = new Msg { type = MsgType.DELAYRESPONSE };

        public Msg OnRequestAvailable(Sample<Msg> request)
        {
            Console.WriteLine("Master: request received.");

            if (request.Info.valid_data)
            {
                reply.type = MsgType.DELAYRESPONSE;
                reply.value = (ulong)MsgPublisher.getCurrentTime();
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

    public static void Main(string[] args) {
    
        // --- Run --- //
        try 
        {
            MsgPublisher.publish(domain_id: 0, sample_count: 0);
        }
        catch(DDS.Exception e)
        {
            Console.WriteLine("error in publisher: " +  e.Message);
        }
    }

    static void publish(int domain_id, int sample_count) {

        /* To customize participant QoS, use 
           the configuration file USER_QOS_PROFILES.xml */
        var participant = DomainParticipantFactory.get_instance().create_participant(
                domain_id,
                DomainParticipantFactory.PARTICIPANT_QOS_DEFAULT, 
                null /* listener */,
                StatusMask.STATUS_MASK_NONE);
        if (participant == null) 
        {
            shutdown(participant);
            throw new ApplicationException("create_participant error");
        }

        var replier = new SimpleReplier<Msg, Msg>(participant, "PTP", new MsgReplierListener(), 
                                                    MsgTypeSupport.get_instance(), MsgTypeSupport.get_instance());
        

        // --- Create publisher --- //

        /* To customize publisher QoS, use 
           the configuration file USER_QOS_PROFILES.xml */
        var publisher = participant.create_publisher(DomainParticipant.PUBLISHER_QOS_DEFAULT, null /* listener */, StatusMask.STATUS_MASK_NONE);
        if (publisher == null) 
        {
            shutdown(participant);
            throw new ApplicationException("create_publisher error");
        }

        // --- Create topic --- //

        /* Register type before creating topic */
        var type_name = MsgTypeSupport.get_type_name();
        try 
        {
            MsgTypeSupport.register_type(participant, type_name);
        }
        catch(DDS.Exception e) 
        {
            Console.WriteLine("register_type error {0}", e);
            shutdown(participant);
            throw e;
        }

        /* To customize topic QoS, use 
           the configuration file USER_QOS_PROFILES.xml */
        var topic = participant.create_topic("PTP", type_name, DomainParticipant.TOPIC_QOS_DEFAULT, null /* listener */, StatusMask.STATUS_MASK_NONE);
        if (topic == null) 
        {
            shutdown(participant);
            throw new ApplicationException("create_topic error");
        }

        // --- Create writer --- //

        /* To customize data writer QoS, use 
           the configuration file USER_QOS_PROFILES.xml */
        var writer = publisher.create_datawriter(topic, Publisher.DATAWRITER_QOS_DEFAULT, null /* listener */, StatusMask.STATUS_MASK_NONE);
        //writer.set_qos_with_profile("PTPMsgs_Library", "PTPMsgs_DataWriter");
        if (writer == null) 
        {
            shutdown(participant);
            throw new ApplicationException("create_datawriter error");
        }
        var Msg_writer = (MsgDataWriter)writer;

        // --- Write --- //

        /* Create data sample for writing */
        var instance = MsgTypeSupport.create_data();
        if (instance == null) 
        {
            shutdown(participant);
            throw new ApplicationException("MsgTypeSupport.create_data error");
        }

        /* For a data type that has a key, if the same instance is going to be
           written multiple times, initialize the key here
           and register the keyed instance prior to writing */
        var instance_handle = InstanceHandle_t.HANDLE_NIL;
        /*
        instance_handle = Msg_writer.register_instance(instance);
        */

        /* Main loop */
        const int send_period = 485; // milliseconds
        var rand = new Random();
        for (int count=0; (sample_count == 0) || (count < sample_count); ++count) 
        {
            var tm = (ulong)getCurrentTime();

            //Console.WriteLine("Master: sending {0}", instance.value / 10 / 1000);

            try 
            {
                instance.type = MsgType.SYNC;
                instance.value = tm + (ulong)rand.Next(10000);
                Msg_writer.write(instance, ref instance_handle);

                instance.type = MsgType.FOLLOWUP;
                instance.value = tm;
                Msg_writer.write(instance, ref instance_handle);
            }
            catch(DDS.Exception e) 
            {
                Console.WriteLine("write error {0}", e);
            }

            Thread.Sleep(send_period);
        }

        /*
        try {
            Msg_writer.unregister_instance(
                instance, ref instance_handle);
        } catch(DDS.Exception e) {
            Console.WriteLine("unregister instance error: {0}", e);
        }
        */

        // --- Shutdown --- //

        /* Delete data sample */
        try 
        {
            MsgTypeSupport.delete_data(instance);
        } 
        catch(DDS.Exception e) 
        {
            Console.WriteLine("MsgTypeSupport.delete_data error: {0}", e);
        }

        /* Delete all entities */
        shutdown(participant);
    }

    public static long getCurrentTime()
    {
        return DateTime.Now.Ticks;
    }

    static void shutdown(DomainParticipant participant) 
    {
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
            Console.WriteLine("finalize_instance error: {0}", e);
            throw e;
        }
    }
}


} /* namespace PTP */
