/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from PTPMsgs.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#include "PTPMsgsSupport.h"
#include "PTPMsgsPlugin.h"


using namespace System;
using namespace DDS;
    
namespace PTP{

/* ========================================================================= */

// ---------------------------------------------------------------------------
// MsgDataWriter
// ---------------------------------------------------------------------------

MsgDataWriter::MsgDataWriter(
        System::IntPtr impl) : DDS::TypedDataWriter<Msg^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// MsgDataReader
// ---------------------------------------------------------------------------

MsgDataReader::MsgDataReader(
        System::IntPtr impl) : DDS::TypedDataReader<Msg^>(impl) {
    // empty
}


// ---------------------------------------------------------------------------
// MsgTypeSupport
// ---------------------------------------------------------------------------

MsgTypeSupport::MsgTypeSupport()
        : DDS::TypedTypeSupport<Msg^>(
            MsgPlugin::get_instance()) {

    _type_plugin = MsgPlugin::get_instance();
}

void MsgTypeSupport::register_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->register_type_untyped(participant, type_name);
}

void MsgTypeSupport::unregister_type(
        DDS::DomainParticipant^ participant,
        System::String^ type_name) {

    get_instance()->unregister_type_untyped(participant, type_name);
}

Msg^ MsgTypeSupport::create_data() {
    return gcnew Msg();
}

Msg^ MsgTypeSupport::create_data_untyped() {
    return create_data();
}

void MsgTypeSupport::delete_data(
        Msg^ a_data) {
    /* If the generated type does not implement IDisposable (the default),
     * the following will no a no-op.
     */
    delete a_data;
}

void MsgTypeSupport::print_data(Msg^ a_data) {
     get_instance()->_type_plugin->print_data(a_data, nullptr, 0);
}

void MsgTypeSupport::copy_data(
        Msg^ dst, Msg^ src) {

    get_instance()->copy_data_untyped(dst, src);
}

System::String^ MsgTypeSupport::get_type_name() {
    return TYPENAME;
}

System::String^ MsgTypeSupport::get_type_name_untyped() {
    return TYPENAME;
}

DDS::DataReader^ MsgTypeSupport::create_datareaderI(
        System::IntPtr impl) {

    return gcnew MsgDataReader(impl);
}

DDS::DataWriter^ MsgTypeSupport::create_datawriterI(
        System::IntPtr impl) {

    return gcnew MsgDataWriter(impl);
}

MsgTypeSupport^
MsgTypeSupport::get_instance() {
    if (_singleton == nullptr) {
        _singleton = gcnew MsgTypeSupport();
    }
    return _singleton;
}
    
} /* namespace PTP */
