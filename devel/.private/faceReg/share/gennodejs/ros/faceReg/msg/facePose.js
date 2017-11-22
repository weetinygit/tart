// Auto-generated. Do not edit!

// (in-package faceReg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class facePose {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.trans_x = null;
      this.trans_y = null;
      this.trans_z = null;
      this.rot_x = null;
      this.rot_y = null;
      this.rot_z = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('trans_x')) {
        this.trans_x = initObj.trans_x
      }
      else {
        this.trans_x = 0.0;
      }
      if (initObj.hasOwnProperty('trans_y')) {
        this.trans_y = initObj.trans_y
      }
      else {
        this.trans_y = 0.0;
      }
      if (initObj.hasOwnProperty('trans_z')) {
        this.trans_z = initObj.trans_z
      }
      else {
        this.trans_z = 0.0;
      }
      if (initObj.hasOwnProperty('rot_x')) {
        this.rot_x = initObj.rot_x
      }
      else {
        this.rot_x = 0.0;
      }
      if (initObj.hasOwnProperty('rot_y')) {
        this.rot_y = initObj.rot_y
      }
      else {
        this.rot_y = 0.0;
      }
      if (initObj.hasOwnProperty('rot_z')) {
        this.rot_z = initObj.rot_z
      }
      else {
        this.rot_z = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type facePose
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [trans_x]
    bufferOffset = _serializer.float64(obj.trans_x, buffer, bufferOffset);
    // Serialize message field [trans_y]
    bufferOffset = _serializer.float64(obj.trans_y, buffer, bufferOffset);
    // Serialize message field [trans_z]
    bufferOffset = _serializer.float64(obj.trans_z, buffer, bufferOffset);
    // Serialize message field [rot_x]
    bufferOffset = _serializer.float64(obj.rot_x, buffer, bufferOffset);
    // Serialize message field [rot_y]
    bufferOffset = _serializer.float64(obj.rot_y, buffer, bufferOffset);
    // Serialize message field [rot_z]
    bufferOffset = _serializer.float64(obj.rot_z, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type facePose
    let len;
    let data = new facePose(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [trans_x]
    data.trans_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [trans_y]
    data.trans_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [trans_z]
    data.trans_z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rot_x]
    data.rot_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rot_y]
    data.rot_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rot_z]
    data.rot_z = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 48;
  }

  static datatype() {
    // Returns string type for a message object
    return 'faceReg/facePose';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'efb58ddc3c5f275bf54bdee14c47103a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    float64 trans_x
    float64 trans_y
    float64 trans_z
    float64 rot_x
    float64 rot_y
    float64 rot_z
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new facePose(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.trans_x !== undefined) {
      resolved.trans_x = msg.trans_x;
    }
    else {
      resolved.trans_x = 0.0
    }

    if (msg.trans_y !== undefined) {
      resolved.trans_y = msg.trans_y;
    }
    else {
      resolved.trans_y = 0.0
    }

    if (msg.trans_z !== undefined) {
      resolved.trans_z = msg.trans_z;
    }
    else {
      resolved.trans_z = 0.0
    }

    if (msg.rot_x !== undefined) {
      resolved.rot_x = msg.rot_x;
    }
    else {
      resolved.rot_x = 0.0
    }

    if (msg.rot_y !== undefined) {
      resolved.rot_y = msg.rot_y;
    }
    else {
      resolved.rot_y = 0.0
    }

    if (msg.rot_z !== undefined) {
      resolved.rot_z = msg.rot_z;
    }
    else {
      resolved.rot_z = 0.0
    }

    return resolved;
    }
};

module.exports = facePose;
