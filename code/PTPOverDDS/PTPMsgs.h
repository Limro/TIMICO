/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from PTPMsgs.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#pragma once


struct DDS_TypeCode;
    

using namespace System;
using namespace DDS;

    
namespace PTP{


public enum class MsgType : System::Int32 {
    
    SYNC, 
    FOLLOWUP, 
    DELAYREQUEST, 
    DELAYRESPONSE
};

MsgType MsgType_get_default_value();

public ref class MsgTypeSeq
        : public DDS::UserValueSequence<MsgType> {
public:
    MsgTypeSeq() :
            DDS::UserValueSequence<MsgType>() {
        // empty
    }
    MsgTypeSeq(System::Int32 max) :
            DDS::UserValueSequence<MsgType>(max) {
        // empty
    }
    MsgTypeSeq(MsgTypeSeq^ src) :
            DDS::UserValueSequence<MsgType>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport
NDDSUSERDllExport DDS_TypeCode* MsgType_get_typecode();


public ref struct Msg
        : public DDS::ICopyable<Msg^> {
    // --- Declared members: -------------------------------------------------
  public:            
    
    PTP::MsgType type;
    System::UInt64 value;

    // --- Static constants: -------------------------------------    
public:
    


#define PTP_Msg_LAST_MEMBER_ID 1

    // --- Constructors and destructors: -------------------------------------
  public:
    Msg();

  // --- Utility methods: --------------------------------------------------
  public:
  virtual void clear();

  virtual System::Boolean copy_from(Msg^ src);

    virtual System::Boolean Equals(System::Object^ other) override;

    
    static DDS::TypeCode^ get_typecode();

  private:
    static DDS::TypeCode^ _typecode;

}; // class Msg




public ref class MsgSeq sealed
        : public DDS::UserRefSequence<Msg^> {
public:
    MsgSeq() :
            DDS::UserRefSequence<Msg^>() {
        // empty
    }
    MsgSeq(System::Int32 max) :
            DDS::UserRefSequence<Msg^>(max) {
        // empty
    }
    MsgSeq(MsgSeq^ src) :
            DDS::UserRefSequence<Msg^>(src) {
        // empty
    }
};


  #define NDDSUSERDllExport

NDDSUSERDllExport DDS_TypeCode* Msg_get_typecode();

} /* namespace PTP */
