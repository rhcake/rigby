//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.5
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace Rigby {

public class Window : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal Window(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Window obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~Window() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          RigbyBridgePINVOKE.delete_Window(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public void SetTitle(string title) {
    RigbyBridgePINVOKE.Window_SetTitle(swigCPtr, title);
  }

  public void Create() {
    RigbyBridgePINVOKE.Window_Create(swigCPtr);
  }

  public void Destroy() {
    RigbyBridgePINVOKE.Window_Destroy(swigCPtr);
  }

  public void ConsumeInput() {
    RigbyBridgePINVOKE.Window_ConsumeInput(swigCPtr);
  }

  public Window() : this(RigbyBridgePINVOKE.new_Window(), true) {
  }

}

}