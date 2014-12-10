/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from PTPMsgs.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

    
#pragma unmanaged
#include "ndds/ndds_cpp.h"
#pragma managed

using namespace System;
using namespace System::Collections;
using namespace DDS;
    

#include "PTPMsgs.h"
    
namespace PTP{

/* ========================================================================= */

DDS_TypeCode* MsgType_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member MsgType_g_tc_members[4] =
    {
        {
            (char *)"SYNC",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) MsgType::SYNC, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"FOLLOWUP",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) MsgType::FOLLOWUP, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"DELAYREQUEST",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) MsgType::DELAYREQUEST, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"DELAYRESPONSE",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            (RTICdrLong) MsgType::DELAYRESPONSE, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode MsgType_g_tc = 
    {{
        DDS_TK_ENUM, /* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1, /* Ignored */
        (char *)"PTP::MsgType", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of enumerators */
        MsgType_g_tc_members, /* Enumerators */
        DDS_VM_NONE /* Ignored */
}    };

    if (is_initialized) {
        return &MsgType_g_tc;
    }

    is_initialized = RTI_TRUE;
    return &MsgType_g_tc;
}
MsgType MsgType_get_default_value() {
    return MsgType::SYNC;
}


/* ========================================================================= */
Msg::Msg() {

    type = PTP::MsgType_get_default_value();
            
    value = 0;
            
}

void Msg::clear() {
  
    type = PTP::MsgType_get_default_value();
          
    value = 0;
          
}

  

System::Boolean Msg::copy_from(Msg^ src) {
    Msg^ dst = this;

    dst->type = src->type;
            
    dst->value = src->value;

    return true;
}

Boolean Msg::Equals(Object^ other) {
    if (other == nullptr) {
        return false;
    }        
    if (this == other) {
        return true;
    }

    Msg^ otherObj =
        dynamic_cast<Msg^>(other);
    if (otherObj == nullptr) {
        return false;
    }


    if (type != otherObj->type) {
        return false;
    }
            
    if (value != otherObj->value) {
        return false;
    }
            
    return true;
}



DDS::TypeCode^ Msg::get_typecode() {
    if (_typecode == nullptr) {
        _typecode = gcnew DDS::TypeCode(Msg_get_typecode());
    }
    return _typecode;
}


DDS_TypeCode* Msg_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;


    static DDS_TypeCode_Member Msg_g_tc_members[2]=
    {
        {
            (char *)"type",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"value",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode Msg_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"PTP::Msg", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of members */
        Msg_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Msg*/

    if (is_initialized) {
        return &Msg_g_tc;
    }


    Msg_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)PTP::MsgType_get_typecode();
    Msg_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulonglong;

    is_initialized = RTI_TRUE;

    return &Msg_g_tc;
}

} /* namespace PTP */
