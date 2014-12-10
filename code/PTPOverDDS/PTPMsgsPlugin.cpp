/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from PTPMsgs.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#include "PTPMsgsPlugin.h"


#pragma unmanaged
#include "ndds/ndds_cpp.h"
#include "osapi/osapi_utility.h"
#pragma managed

using namespace System::Runtime::InteropServices;
    
namespace PTP{


/* ------------------------------------------------------------------------
  Enum Type: MsgType
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */


Boolean
MsgTypePlugin::serialize(
    TypePluginEndpointData^ endpoint_data,
    MsgType sample,
    CdrStream% stream, 
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_sample,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (serialize_encapsulation) {
        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (serialize_sample) {

        if (!stream.serialize_enum(sample)) {
            return false;
        }

    }


    if (serialize_encapsulation) {
        stream.restore_alignment(position);

    }

    return true;
}


Boolean 
MsgTypePlugin::deserialize_sample(
    TypePluginEndpointData^ endpoint_data,
    MsgType% sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_data, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (deserialize_data) {


        sample = stream.deserialize_enum<MsgType>();

        switch (sample) {

            case MsgType::SYNC:

            case MsgType::FOLLOWUP:

            case MsgType::DELAYREQUEST:

            case MsgType::DELAYRESPONSE:

            {
            } break;
            default:
            {
                throw gcnew Unassignable("invalid enumerator " + sample.ToString());
            } break;
        }

    }

    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
MsgTypePlugin::skip(
    TypePluginEndpointData^ endpoint_data,
    CdrStream% stream, 
    Boolean skip_encapsulation,  
    Boolean skip_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (skip_encapsulation) {
        if (!stream.skip_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }
    if (skip_sample) {

        if (!stream.skip_enum()) {
            return false;
        }


    }


    if(skip_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


UInt32
MsgTypePlugin::get_serialized_sample_max_size(
    TypePluginEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{
    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }

    current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);


    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }


    return current_alignment - initial_alignment;
}


UInt32
MsgTypePlugin::get_serialized_sample_min_size(
    TypePluginEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{
    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }

    current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);


    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }


    return current_alignment - initial_alignment;
}


UInt32
MsgTypePlugin::get_serialized_sample_size(
    TypePluginEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    MsgType sample) 
{
    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }

    current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);


    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }


    return current_alignment - initial_alignment;
}

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */


Boolean
MsgTypePlugin::serialize_key(
    TypePluginEndpointData^ endpoint_data,
    MsgType sample,
    CdrStream% stream,
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_key,
    Object^ endpoint_plugin_qos)
{
    return serialize(
            endpoint_data, sample, stream, serialize_encapsulation, 
            encapsulation_id, 
            serialize_key, endpoint_plugin_qos);
}


Boolean
MsgTypePlugin::deserialize_key_sample(
    TypePluginEndpointData^ endpoint_data,
    MsgType% sample,
    CdrStream% stream,
    Boolean deserialize_encapsulation,
    Boolean deserialize_key,
    Object^ endpoint_plugin_qos)
{
    return deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);
}


UInt32
MsgTypePlugin::get_serialized_key_max_size(
    TypePluginEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{
    UInt32 initial_alignment = current_alignment;

    current_alignment += get_serialized_sample_max_size(
        endpoint_data,include_encapsulation,
        encapsulation_id,current_alignment);

    return current_alignment - initial_alignment;
}


Boolean
MsgTypePlugin::serialized_sample_to_key(
    TypePluginEndpointData^ endpoint_data,
    MsgType% sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_key, 
    Object^ endpoint_plugin_qos)
{    
    return deserialize_sample(
            endpoint_data,
            sample,
            stream,
            deserialize_encapsulation, 
            deserialize_key,
            endpoint_plugin_qos);
}


/* ------------------------------------------------------------------------
   Support functions:
 * ------------------------------------------------------------------------ */


void
MsgTypePlugin::print_data(
    MsgType sample,
    String^ description,
    UInt32 indent_level)
{
    if (description != nullptr) {
        for (UInt32 i = 0; i < indent_level; ++i) { Console::Write("   "); }
        Console::WriteLine("{0}:", description);
    }

    RTICdrType_printEnum((RTICdrEnum*) &sample,
                         "MsgType", indent_level + 1);
}


/* ------------------------------------------------------------------------
 * Plug-in Lifecycle Methods
 * ------------------------------------------------------------------------ */

MsgTypePlugin^
MsgTypePlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew MsgTypePlugin();
    }
    return _singleton;
}


void
MsgTypePlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}


/* ------------------------------------------------------------------------
 *  Type Msg
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
    Support functions:
 * ------------------------------------------------------------------------ */

void 
MsgPlugin::print_data(
        Msg^ sample,
        String^ desc,
        UInt32 indent_level) {

    for (UInt32 i = 0; i < indent_level; ++i) { Console::Write("   "); }

    if (desc != nullptr) {
        Console::WriteLine("{0}:", desc);
    } else {
        Console::WriteLine();
    }

    if (sample == nullptr) {
        Console::WriteLine("null");
        return;
    }


    DataPrintUtility::print_object(
        sample->type, "type", indent_level);
            
    DataPrintUtility::print_object(
        sample->value, "value", indent_level);
            
}


/* ------------------------------------------------------------------------
    (De)Serialize functions:
 * ------------------------------------------------------------------------ */

Boolean 
MsgPlugin::serialize(
    TypePluginDefaultEndpointData^ endpoint_data,
    Msg^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    

    if (serialize_encapsulation) {
        /* Encapsulate sample */
        
        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_sample) {

    if (!PTP::MsgTypePlugin::get_instance()->serialize(
            endpoint_data,
            sample->type,
            stream,
            false, // serialize encapsulation
            encapsulation_id,
            true,  // serialize data 
            endpoint_plugin_qos)) {
        return false;
    }
            
    if (!stream.serialize_unsigned_long_long(sample->value)) {
        return false;
    }
            
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean 
MsgPlugin::deserialize_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    Msg^ sample,
    CdrStream% stream,   
    Boolean deserialize_encapsulation,
    Boolean deserialize_data, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (deserialize_data) {
        sample->clear();

    try {
  
    if (!PTP::MsgTypePlugin::get_instance()->deserialize_sample(
            endpoint_data,
            sample->type,
            stream,
            false, // deserialize encapsulation
            true,  // deserialize data
            endpoint_plugin_qos)) {
        return false;
    }
            
    sample->value = stream.deserialize_unsigned_long_long();
            
    } catch (System::ApplicationException^  e) {
        if (stream.get_remainder() >= RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
            throw gcnew System::ApplicationException("Error deserializing sample! Remainder: " + stream.get_remainder() + "\n" +
                                                              "Exception caused by: " + e->Message);
        }
    }

    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
MsgPlugin::skip(
    TypePluginDefaultEndpointData^ endpoint_data,
    CdrStream% stream,   
    Boolean skip_encapsulation,
    Boolean skip_sample, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;


    if (skip_encapsulation) {
        if (!stream.skip_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (skip_sample) {

    if (!PTP::MsgTypePlugin::get_instance()->skip(
            endpoint_data,
            stream, 
            false, true, 
            endpoint_plugin_qos)) {
        return false;
    }
            
    if (!stream.skip_unsigned_long_long()) {
        return false;
    }
            
    }


    if(skip_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}

/*
  size is the offset from the point where we have do a logical reset
  Return difference in size, not the final offset.
*/
UInt32 
MsgPlugin::get_serialized_sample_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  PTP::MsgTypePlugin::get_instance()->get_serialized_sample_max_size(
        endpoint_data, false, encapsulation_id, current_alignment);
            
    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
MsgPlugin::get_serialized_sample_min_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            encapsulation_size);
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  PTP::MsgTypePlugin::get_instance()->get_serialized_sample_min_size(
        endpoint_data, false, encapsulation_id, current_alignment);
            
    current_alignment +=  CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32 
MsgPlugin::get_serialized_sample_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment,
    Msg^ sample)
{

    UInt32 initial_alignment = current_alignment;

    UInt32 encapsulation_size = current_alignment;


    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += PTP::MsgTypePlugin::get_instance()->get_serialized_sample_size(
        endpoint_data, false, encapsulation_id, current_alignment, sample->type);
            
    current_alignment += CdrSizes::LONG_LONG->serialized_size(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


UInt32
MsgPlugin::get_serialized_key_max_size(
    TypePluginDefaultEndpointData^ endpoint_data,
    Boolean include_encapsulation,
    UInt16 encapsulation_id,
    UInt32 current_alignment)
{

    UInt32 encapsulation_size = current_alignment;


    UInt32 initial_alignment = current_alignment;

    if (include_encapsulation) {
        if (!CdrStream::valid_encapsulation_id(encapsulation_id)) {
            return 1;
        }


        encapsulation_size = CdrSizes::ENCAPSULATION->serialized_size(
            current_alignment);
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment += get_serialized_sample_max_size(
        endpoint_data,false,encapsulation_id,current_alignment);
    
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

Boolean 
MsgPlugin::serialize_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    Msg^ sample,
    CdrStream% stream,    
    Boolean serialize_encapsulation,
    UInt16 encapsulation_id,
    Boolean serialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (serialize_encapsulation) {
        /* Encapsulate sample */

        if (!stream.serialize_and_set_cdr_encapsulation(encapsulation_id)) {
            return false;
        }


        position = stream.reset_alignment();

    }

    if (serialize_key) {

        if (!serialize(
                endpoint_data,
                sample,
                stream,
                serialize_encapsulation,
                encapsulation_id, 
                serialize_key,
                endpoint_plugin_qos)) {
            return false;
        }
    
    }


    if(serialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean MsgPlugin::deserialize_key_sample(
    TypePluginDefaultEndpointData^ endpoint_data,
    Msg^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,
    Boolean deserialize_key,
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if (deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;  
        }


        position = stream.reset_alignment();

    }

    if (deserialize_key) {

        if (!deserialize_sample(
                endpoint_data, sample, stream,
                deserialize_encapsulation,
                deserialize_key,
                endpoint_plugin_qos)) {
            return false;
        }
    
    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}


Boolean
MsgPlugin::serialized_sample_to_key(
    TypePluginDefaultEndpointData^ endpoint_data,
    Msg^ sample,
    CdrStream% stream, 
    Boolean deserialize_encapsulation,  
    Boolean deserialize_key, 
    Object^ endpoint_plugin_qos)
{
    CdrStreamPosition position;

    if(deserialize_encapsulation) {
        if (!stream.deserialize_and_set_cdr_encapsulation()) {
            return false;
        }

        position = stream.reset_alignment();

    }

    if (deserialize_key) {

        if (!deserialize_sample(
                endpoint_data,
                sample,
                stream,
                deserialize_encapsulation,
                deserialize_key,
                endpoint_plugin_qos)) {
            return false;
        }

    }


    if(deserialize_encapsulation) {
        stream.restore_alignment(position);
    }


    return true;
}




/* ------------------------------------------------------------------------
 * Plug-in Lifecycle Methods
 * ------------------------------------------------------------------------ */

MsgPlugin^
MsgPlugin::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew MsgPlugin();
    }
    return _singleton;
}


void
MsgPlugin::dispose() {
    delete _singleton;
    _singleton = nullptr;
}

} /* namespace PTP */
