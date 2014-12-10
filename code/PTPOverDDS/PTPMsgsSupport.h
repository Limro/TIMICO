/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from PTPMsgs.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#pragma once

#include "PTPMsgs.h"


class DDSDataWriter;
class DDSDataReader;
    
namespace PTP{

// ---------------------------------------------------------------------------
// MsgTypeSupport
// ---------------------------------------------------------------------------

ref class MsgPlugin;

/* A collection of useful methods for dealing with objects of type
 * Msg.
 */
public ref class MsgTypeSupport
        : public DDS::TypedTypeSupport<Msg^> {
    // --- Type name: --------------------------------------------------------
  public:
    static System::String^ TYPENAME = "PTP::Msg";


    // --- Public Methods: ---------------------------------------------------
  public:
    /* Get the default name of this type.
     *
     * An application can choose to register a type under any name, so
     * calling this method is strictly optional.
     */
    static System::String^ get_type_name();

    /* Register this type with the given participant under the given logical
     * name. This type must be registered before a Topic can be created that
     * uses it.
     */
    static void register_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Unregister this type from the given participant, where it was
     * previously registered under the given name. No further Topic creation
     * using this type will be possible.
     *
     * Unregistration allows some middleware resources to be reclaimed.
     */
    static void unregister_type(
            DDS::DomainParticipant^ participant,
            System::String^ type_name);

    /* Create an instance of the Msg type.
     */
    static Msg^ create_data();

    /* If instances of the Msg type require any
     * explicit finalization, perform it now on the given sample.
     */
    static void delete_data(Msg^ data);

    /* Write the contents of the data sample to standard out.
     */
    static void print_data(Msg^ a_data);

    /* Perform a deep copy of the contents of one data sample over those of
     * another, overwriting it.
     */
    static void copy_data(
        Msg^ dst_data,
        Msg^ src_data);


    // --- Implementation: ---------------------------------------------------
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
public:
    virtual DDS::DataReader^ create_datareaderI(
        System::IntPtr impl) override;
    virtual DDS::DataWriter^ create_datawriterI(
        System::IntPtr impl) override;
        
    virtual Msg^ create_data_untyped() override;
    
    virtual System::String^ get_type_name_untyped() override;
        

public:
    static MsgTypeSupport^ get_instance();

    MsgTypeSupport();

private:
    static MsgTypeSupport^ _singleton;
    MsgPlugin^ _type_plugin;
};


// ---------------------------------------------------------------------------
// MsgDataReader
// ---------------------------------------------------------------------------

/**
 * A reader for the Msg type.
 */
public ref class MsgDataReader :
        public DDS::TypedDataReader<Msg^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    MsgDataReader(System::IntPtr impl);
};


// ---------------------------------------------------------------------------
// MsgDataWriter
// ---------------------------------------------------------------------------

/**
 * A writer for the Msg user type.
 */
public ref class MsgDataWriter :
        public DDS::TypedDataWriter<Msg^> {
    /* The following code is for the use of the middleware infrastructure.
     * Applications are not expected to call it directly.
     */
  internal:
    MsgDataWriter(System::IntPtr impl);
};

} /* namespace PTP */
